#! /usr/bin/python

import numpy as np

r1 = input ("Enter the quantity of rows to first matrix: ")
c1 = input ("Enter the quantity of columns to first matrix: ")
r2 = input ("Enter the quantity of rows to second matrix: ")
c2 = input ("Enter the quantity of columns to second matrix: ")

if (c1!=r1): 
	print("Columns of the first matrix need to be equal the second matrix")
	quit()

#Filling First Matrix Values
m1 = np.random.randint(1,10,size=(r1,c1))
m2 = np.random.randint(1,10,size=(r2,c2))
print(m1)
print(m2)
mult = np.matmul(m1, m2)
print(mult)
