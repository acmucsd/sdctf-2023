N = 107 # must be prime

def mul(a, b):
    return (a * b) % N

def inv(a):
    t = 0
    r = N
    nt = 1
    nr = a
    while nr != 0:
        q = r // nr
        rem = r % nr
        # t, nt = nt, (t - mul(q, nt)) % N
        t, nt = nt, (t + mul(q, N-nt)) % N
        # WARNING: when implementing subtraction in C, be careful not to underflow/overflow mod 2^64, can always multiply by (n-1) mod n
        r, nr = nr, rem
    assert r == 1
    return t

for i in range(1, N):
    assert (inv(i) * i) % N == 1