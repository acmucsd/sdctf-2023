# See solve/ folder for hashclash usage
# In solve, run:
# /path/to/hashclash/scripts/cpc.sh rock.txt paper.txt
# To generate solve/{rock.txt.coll,paper.txt.coll}

from pwnlib.tubes import remote, process
import base64
import sys

HOST = 'rps.sdc.tf'
PORT = 1337

rock_proof = open('solve/rock.txt.coll', 'rb').read()
paper_proof = open('solve/paper.txt.coll', 'rb').read()
common_hash = bytes.fromhex('fe206f0fdbf7db6d9ddd50e07a2238d5')

# print(rock)
# print(paper)

r = remote.remote(HOST, PORT)
# r = process.process(['python3', 'server.py'])

def send(msg: str) -> None:
    r.sendline(msg.encode())

def send_data(msg: bytes) -> None:
    r.sendline(base64.b64encode(msg))

def recv() -> str:
    return r.recvline(keepends=False).decode()

def recv_command() -> 'tuple[str, str]':
    cmd, arg = recv().split(maxsplit=1)
    if cmd == '==': # skip proof-of-work if any
        cmd, arg = recv().split(maxsplit=1)
    return cmd, arg

def error(err: str):
    print(f'Server error: {err}')
    sys.exit(1)

def process_command():
    cmd, arg = recv_command()
    if cmd == 'ERROR':
        error(arg)
    elif cmd == 'MOVE':
        print(f'Server move: {arg}')
    elif cmd == 'VERDICT':
        print(f'Server verdict: {arg}')
        if arg == 'Client lost':
            print('Game over!')
            sys.exit(0)
    elif cmd == 'FLAG':
        print(f'You won the flag: {arg}')
        sys.exit(0)
    elif cmd == 'NEXT':
        print('Your turn!')
    else:
        error(f'Unknown command: {cmd}')
    return cmd, arg

process_command()

while True:
    commitment = common_hash
    send_data(commitment)
    cmd, arg = process_command()
    assert cmd == 'MOVE'
    if arg == 'P': # Can have a draw by sending paper also
        send_data(paper_proof)
    else: # Rock draws with rock and beats scissors
        send_data(rock_proof)
    process_command()
    process_command()
