#!/usr/bin/env python

import sys

def processName(name):
    ret = name.replace('\'', '_')
    return ret

def main():
    if len(sys.argv) != 2:
        print("usage: fsmIncGen.py [FSMNAME]")
        return

    name = sys.argv[1]
    sigFileName = name + '.sig'
    staFileName = name + '.sta'

    memberIncFileName = name + 'Member.inc'
    initIncFileName = name + 'Init.inc'

    f = open(sigFileName, 'r')
    sigs = f.readlines()
    f.close()

    f = open(staFileName, 'r')
    stas = f.readlines()
    f.close()

    memberInc = []
    initInc = []

    for sig in sigs:
        sig = sig.strip()
        sigp = processName(sig)
        if len(sig) != 0:
            memberInc.append('int _%sSig;\n' % sigp)
            initInc.append('_%sSig = getSignalId(\"%s\");\n' % (sigp, sig))

    for sta in stas:
        sta = sta.strip()
        stap = processName(sta)
        if len(sta) != 0:
            memberInc.append('int _%sSta;\n' % stap)
            initInc.append('_%sSta = getStateId(\"%s\");\n' % (stap, sta))

    f = open(memberIncFileName, 'w')
    f.writelines(memberInc)
    f.close()

    f = open(initIncFileName, 'w')
    f.writelines(initInc)
    f.close()

if __name__ == "__main__":
    main()
