#! /usr/bin/python

import sys
import numpy as np

if (len(sys.argv)!=2):
    print("ERROR: Insuficient Arguments")
    quit()

d = int(sys.argv[1])

#Filling First Matrix Values
m1 = np.random.randint(1,10,size=(d,d))
m2 = np.random.randint(1,10,size=(d,d))
#print(m1)
#print(m2)
mult = np.matmul(m1, m2)
#print(mult)
