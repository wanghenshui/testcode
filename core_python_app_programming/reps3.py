#!/usr/bin/python3

import os
import re

with os.popen('ps','r') as f:
    for each_line in f:
        print(re.split(r'\s\s+|\t',each_line.strip()))
        
