#!/usr/bin/python

import os
import sys
import zipfile

if sys.version_info.major == 3:
    import urllib.request as urllib2
else:
    import urllib2

workpath = os.path.dirname(os.path.realpath(__file__))

def download(filename, url):
    print("Downloading '%s' from '%s'..." % (filename, url))
    u = urllib2.urlopen(url)
    f = open(os.path.join(workpath, filename), 'wb')
    f.write(u.read())
    f.close()
    print("Finished!")

def extract_to(filename, dirname):
    zfile = zipfile.ZipFile(filename, 'r')
    for ef in zfile.namelist():
        if ef.endswith('/'):
            continue
        p = os.path.join(dirname, ef)
        d = os.path.dirname(p)
        if not os.path.exists(d):
            os.makedirs(d)
        f = open(p, 'wb')
        f.write(zfile.read(ef))
        f.close()
    zfile.close()

def extract(filename):
    extract_to(os.path.join(workpath, filename), workpath)

def main():
    # download("deps.zip", "http://www.fountainment.com/download/deps.zip")
    # download("res.zip", "http://www.fountainment.com/download/res.zip")

    extract("deps.zip")
    extract("res.zip")

if __name__ == '__main__':
    main()
