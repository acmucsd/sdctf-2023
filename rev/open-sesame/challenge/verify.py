# Internal file used to verify the challenge is solvable and generate data for sesame.py
from sesame import gencave, MOD
from sage.all import matrix, vector, Integers

FLAG = b'sdctf{0p3n_s3sAm3_bUt_1n_l337Sp3aK!}'

F = Integers(MOD)

cave = gencave(len(FLAG))
cmat = matrix(F, cave)
fv = vector(F, list(FLAG))
assert cmat.is_invertible(), 'No solution!'
res = cmat * fv
print(f'FLAG_LEN = {len(FLAG)}')
print(f'DOOR_SHAPE = {list(res)}')
