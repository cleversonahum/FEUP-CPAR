#! /usr/bin/python

import sys
import numpy as np

if (len(sys.argv)!=3):
    print("ERROR: Insuficient Arguments")
    quit()

if (sys.argv[2]!=sys.argv[1]): 
    print("ERROR: Columns of the first matrix need to be equal the second matrix")
    quit()

r = int(sys.argv[1] )
c = int(sys.argv[2])

#Filling First Matrix Values
m1 = np.random.randint(1,10,size=(r,c))
m2 = np.random.randint(1,10,size=(r,c))
#print(m1)
#print(m2)
mult = np.matmul(m1, m2)
#print(mult)
