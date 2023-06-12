from sage.all import is_prime, GF
# import random
import secrets

# p = 7
# # MUST be safe prime
# assert is_prime(p)
# assert is_prime((p - 1) // 2)

PAD_LEN = 64 - 39

# random.seed(10803717371130737497)

HEX = '0123456789abcdef'

pad = ''.join(secrets.choice(HEX) for _ in range(PAD_LEN))

flag_seg_1 = 'sQU&Mu1t'
assert len(flag_seg_1) == 8

# print(FLAG)

P_BITS = 63

def large_safe_prime(nbits: int):
    p = 2 ** P_BITS - 1
    while True:
        if is_prime(p) and is_prime((p - 1) // 2):
            return p
        p -= 2

p = large_safe_prime(P_BITS)

F = GF(p)

order = p - 1

c = -1
for c in range(1, 100):
    if F(c).multiplicative_order() == order:
        break

print(f'#define P ({hex(p)})')
print(f'#define C ({c})')

y = secrets.randbelow(order)
x = pow(c, y, p)
f = int.from_bytes(flag_seg_1.encode(), 'little')
assert 0 <= f < p
f_enc = (f * pow(x, -1, p)) % p
assert((f_enc * x) % p == f)
# print(f'{f = }') # DEBUG
print(f'#define FLAG_ENC ({f_enc}ULL)')
print(f'#define GENERATION_COUNT ({y})')

print(f'// FLAG: sdctf{{{flag_seg_1}_{x}}}')
