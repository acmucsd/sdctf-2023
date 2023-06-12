from pwn import *
import hlextend

def xor(sa: bytes, sb: bytes):
    return bytes([a ^ b for a, b in zip(sa, sb)])

COUNTER_SIZE = 256
COUNTER_SIZE_BYTES = COUNTER_SIZE // 8

# r = remote('localhost', 1337)
r = process(['python3', 'sha256ctr.py'])

ZERO_BLOCK = b'0' * 64 # SHA-256: 32 bytes

r.recvuntil(b'> ')
r.sendline(b'2')
r.sendline(ZERO_BLOCK)
r.recvuntil(b'Ciphertext in hex: ')
first_block = r.recvline(keepends=False).decode()

sha = hlextend.sha256()
counter_pad = sha.extend(b'\x01', b'', COUNTER_SIZE_BYTES, first_block)
final_hash = sha.hexdigest()

increment = int.from_bytes(b'\0' * COUNTER_SIZE_BYTES + counter_pad, byteorder='little')

r.recvuntil(b'> ')
r.sendline(b'3')
r.recvuntil(b'N = ')
r.sendline(str(increment - 1).encode())

r.recvuntil(b'> ')
r.sendline(b'1')
r.recvuntil(b'text in hex: ')
flag_enc = r.recvline().decode()
# For flags longer than 32 bytes/256-bits (output size of SHA-256)
# can use a similar strategy by collecting known hash values for more consecutive counters
# and performing multiple length extension attacks
# TODO: left as an exercise for the reader
print(xor(bytes.fromhex(flag_enc), bytes.fromhex(final_hash)))
