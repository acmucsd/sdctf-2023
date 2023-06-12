#! /usr/bin/env python3
import base64

coded_flag = "c2RjdGZ7VV91blJhdjNsZWRfdEgzX3NuM2shfQ=="

def reverse(s):
    return "".join(reversed(s))

def check():
    """GOD_YZAL_EHT_REVO_SPMUJ_XOF_NWORB_KCIUQ_EHT"""
    assert decode_flag.__doc__ is not None and decode_flag.__doc__.upper()[2:45] == reverse(check.__doc__)

def decode_flag(code):
    """{'the_quick_brown_fox_jumps_over_the_lazy_dog': 123456789.0, 'items':[]}"""
    return base64.b64decode(code).decode()

if __name__ == "__main__":
    check()
    print(decode_flag(coded_flag))
