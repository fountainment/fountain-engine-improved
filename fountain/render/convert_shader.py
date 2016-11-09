#!/usr/bin/env python

import sys

def convert_str(infile, outfile):
    f = open(infile, 'r')
    lines = f.readlines()
    f.close()
    f = open(outfile, 'w')
    f.writelines(['"%s\\n"\n' % i.rstrip() for i in lines])
    f.close()

def main():
    convert_str('fountain.vert', 'fountain.vert.inc')
    convert_str('fountain.frag', 'fountain.frag.inc')

if __name__ == '__main__':
    main()
