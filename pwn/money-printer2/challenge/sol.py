from pwn import *
#must be run in bin to work

#gdb.attach(p)

p.sendline(payload)
p.interactive()
