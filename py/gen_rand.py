#/usr/bin/python3

import random
import sys

l = []
counter = 256
while counter:
    l.append(random.randint(0,sys.maxsize))
    counter = counter -1

print(l)
