#!/usr/bin/python

import os
import re


f = os.popen('ps','r')

for each_line in f:
    print re.split(r'\s\s+',each_line.rstrip())

f.close()
