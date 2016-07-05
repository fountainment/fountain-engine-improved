#!/usr/bin/env python

import os, sys

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
    aniFileName = name + '.ani'

    memberIncFileName = name + 'Member.inc'
    initIncFileName = name + 'Init.inc'
    sigs = []
    stas = []
    anis = []

    if os.path.exists(sigFileName):
        f = open(sigFileName, 'r')
        sigs = f.readlines()
        f.close()

    if os.path.exists(staFileName):
        f = open(staFileName, 'r')
        stas = f.readlines()
        f.close()

    if os.path.exists(aniFileName):
        f = open(aniFileName, 'r')
        anis = f.readlines()
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

    staName = ''
    aniIndex = 0
    for ani in anis:
        ani = ani.strip().split()
        lani = len(ani)
        if lani == 0:
            continue
        if lani == 1:
            staName = processName(ani[0])
            aniIndex = 0
        else:
            aniVarName = staName + 'Anime'
            mapName = 'stateBaseAnimeMap'
            if aniIndex != 0:
                aniVarName = staName + 'EffectAnime'
                mapName = 'stateEffectAnimeMap'
            initInc.append('_%s[_%sSta] = &_%s;\n' % (mapName, staName, aniVarName))
            initInc.append('_%s.loadImageFileAndIPI(\"%s\");\n' % (aniVarName, ani[0]))
            initInc.append('_%s.setFps(%s);\n' % (aniVarName, ani[1]))
            loop = 'false'
            if ani[2] == 't':
                loop = 'true'
            initInc.append('_%s.setLoop(%s);\n' % (aniVarName, loop))
            if lani == 3:
                memberInc.append('fei::FrameAnime _%s;\n' % aniVarName)
            if lani == 4:
                memberInc.append('fut::CollisionFrameAnime _%s;\n' % aniVarName)
                initInc.append('_%s.loadCollisionFile(\"%s\");\n' % (aniVarName, ani[3]))
            aniIndex += 1

    f = open(memberIncFileName, 'w')
    f.writelines(memberInc)
    f.close()

    f = open(initIncFileName, 'w')
    f.writelines(initInc)
    f.close()

if __name__ == "__main__":
    main()
