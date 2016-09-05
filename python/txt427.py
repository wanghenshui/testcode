# -*- coding: cp936 -*-
#usage:python pyplot.py filename.txt colsToPlot
#colsToPlot is seperated by comma(",")
#example:python pyplot.py cpuRatio1.txt 2,4,5,7
#get data in cpuRatio1.txt and plot columns of 2,4,5,7

import numpy as np
import matplotlib as plt
import sys
import string

f = open('Data.txt','r')
print(f)
#content = f.readlines()
#print (content)
content = f.readline()
print (content)
content = f.read()
print (content)

