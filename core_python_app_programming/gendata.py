#!/usr/bin/python

from random import randrange, choice
from string import ascii_lowercase as lc
from sys import maxint
from time import ctime

tlds =('com','edu,','net','org','gov')

for i in xrange(randrange(5,11)):
    dtint = randrange(maxint)
    dtstr = ctime(dtint)
    llen =  randrange(4,8)
    login = ''.join(choice(lc) for j in range(llen))
    dlen = randrange(llen,13)
    dom = ''.join(choice(lc) for j in xrange(dlen))
    print '%s::%s@%s.%s::%d-%d-%d' %(dtstr,login,dom,choice(tlds),dtint,llen,dlen)
