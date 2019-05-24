# -*- coding: utf-8 -*-
"""
Created on Mon Dec 25 11:00:16 2017

@author: erik.toger
"""

from SparseMatrix import SparseMatrix
import unittest

import numpy as np
import numpy.testing as npt

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

import timeit

import matplotlib.pyplot as plt

#import plotly.plotly as py

Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])

"""
Task 1
"""
print()
print('Task 1')
print()
print(Mx)
T=SparseMatrix(Mx)
print(T)

"""
Task 2
"""
print()
print('Task 2')
print()


print(T.number_of_nonzero)

"""
Task 3
"""
print()
print('Task 3')
print()
T.Change_Element(2,1,1) 
print()
print(T)
print(T.number_of_nonzero)
print()

"""
Task 4
"""
print()
print('Task 4')
print()
R=SparseMatrix(Mx)
print(R.intern_represent)
R.CSR_to_CSC_Change()
print(R.intern_represent)

"""
Task 5
"""
print()
print('Task 5')
print()

R=SparseMatrix(Mx)
B=SparseMatrix(Mx)
R=R.CSR_to_CSC()
print(B.CSR_equal_CSC(R))
print(B.CSR_to_CSC().intern_represent)
print(R)

"""
Task 6
"""
print()
print('Task 6')
print()
Mx=np.array([(1,8,2),(0,0.001,3),(0,5,6)])
Mx2=np.array([(0,1,-0.001),(0.001,2,3),(0,0,6)])
A=SparseMatrix(Mx,TOL=0) # det är något vajsings att TOl ärvs till nästa? men nu ör A och B olika så nu syns det inte
B=SparseMatrix(Mx2,TOL=0.01) # Om jag byter plats på dessa två så blir det rätt
print(A)
print(B)
"""
Task 7
"""
print()
print('Task 7')
print()
Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])
C=SparseMatrix(Mx)
D=SparseMatrix(Mx2)
print(C+D)
"""
Task 8
"""
print()
print('Task 8')
print()

Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
E=SparseMatrix(Mx)
V=np.array([1,2,1])

print(E.CSR_x_VECTOR(V))

"""
Task 9
"""
print()
print('Task 9')
print('See Test_SparseMatrix.py')
"""
Task 10
"""

print()
print('Task 10')
print()

setup_statements="""
from SparseMatrix import SparseMatrix
import unittest

import numpy as np
import numpy.testing as npt

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

N= 5
RanMa=np.random.rand(N,N)
RanMa[RanMa>0.80] = 1
RanMa[RanMa<1]=0

RanMa2=np.random.rand(N,N)
RanMa2[RanMa2>0.80] = 1
RanMa2[RanMa2<1]=0

#Mx=RanMa
#Mx2=RanMa2
Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])

mincsr = SparseMatrix(Mx)
inbygdcsr = csr_matrix(Mx)

SparseMatrix(Mx).Change_Element(2,1,1)
mincsr.Change_Element(2,1,1)
Mx[1,1]=2

inbygdcsr[1,1]=2

mincsr2 = SparseMatrix(Mx)
inbygdcsr2 = csr_matrix(Mx)
mincsr3 = SparseMatrix(Mx2)
inbygdcsr3 = csr_matrix(Mx2)

mincsr2+mincsr3
inbygdcsr2+inbygdcsr3
np.add(Mx,Mx2)

mincsr4 = SparseMatrix(Mx)
inbygdcsr4 = csr_matrix(Mx)
V=[1,2,3]
#V = np.random.randint(10,size=N)
mincsr4.CSR_x_VECTOR(V)
inbygdcsr4.dot(V)
Mx.dot(V)
"""

setup_statements1="""
from SparseMatrix import SparseMatrix
import unittest

import numpy as np
import numpy.testing as npt

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

N= 5
RanMa=np.random.rand(N,N)
RanMa[RanMa>0.80] = 1
RanMa[RanMa<1]=0

RanMa2=np.random.rand(N,N)
RanMa2[RanMa2>0.80] = 1
RanMa2[RanMa2<1]=0

Mx=RanMa
Mx2=RanMa2
#Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
#Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])

mincsr = SparseMatrix(Mx)
inbygdcsr = csr_matrix(Mx)

SparseMatrix(Mx).Change_Element(2,1,1)
mincsr.Change_Element(2,1,1)
Mx[1,1]=2

inbygdcsr[1,1]=2

"""
setup_statements2="""
from SparseMatrix import SparseMatrix
import unittest

import numpy as np
import numpy.testing as npt

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

N= 5
RanMa=np.random.rand(N,N)
RanMa[RanMa>0.80] = 1
RanMa[RanMa<1]=0

RanMa2=np.random.rand(N,N)
RanMa2[RanMa2>0.80] = 1
RanMa2[RanMa2<1]=0

Mx=RanMa
Mx2=RanMa2
#Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
#Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])

mincsr = SparseMatrix(Mx)
inbygdcsr = csr_matrix(Mx)

mincsr2 = SparseMatrix(Mx)
inbygdcsr2 = csr_matrix(Mx)
mincsr3 = SparseMatrix(Mx2)
inbygdcsr3 = csr_matrix(Mx2)

mincsr2+mincsr3
inbygdcsr2+inbygdcsr3
np.add(Mx,Mx2)
"""

setup_statements3="""
from SparseMatrix import SparseMatrix
import unittest

import numpy as np
import numpy.testing as npt

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

N= 50
RanMa=np.random.rand(N,N)
RanMa[RanMa>0.80] = 1
RanMa[RanMa<1]=0

RanMa2=np.random.rand(N,N)
RanMa2[RanMa2>0.80] = 1
RanMa2[RanMa2<1]=0

#Mx=RanMa
#Mx2=RanMa2

Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])
#print(Mx)

mincsr4 = SparseMatrix(Mx)

inbygdcsr4 = csr_matrix(Mx)
V=[1,2,3]
#V = np.random.randint(10,size=N)
mincsr4.CSR_x_VECTOR(V)
inbygdcsr4.dot(V)
Mx.dot(V)
"""





n=3
#print('1a')
experiment_1a= timeit.Timer(stmt='mincsr.Change_Element(2,1,1)',setup=setup_statements1) 
t1a=experiment_1a.repeat(3,n)
#print(min(t1a)*1000/n)
T1a = min(t1a)*1000/n
# av någon anledning funkar inte mincsr.Change_Element(2,1,1) när jag kör den i timit

#print('1b')
experiment_1b= timeit.Timer(stmt='inbygdcsr[1,1]=2',setup=setup_statements1) 
t1b=experiment_1b.repeat(3,n)
#print(min(t1b)*1000/n)
T1b = min(t1b)*1000/n

#print('1c')
experiment_1c= timeit.Timer(stmt='Mx[1,1]=2',setup=setup_statements1) 
t1c=experiment_1c.repeat(3,n)
#print(min(t1c)*1000/n)
T1c = min(t1c)*1000/n

#print('2a')
experiment_2a= timeit.Timer(stmt='mincsr2+mincsr3',setup=setup_statements2) 
t2a=experiment_2a.repeat(3,n)
#print(min(t2a)*1000/n)
T2a = min(t2a)*1000/n

#print('2b')
experiment_2b= timeit.Timer(stmt='inbygdcsr2+inbygdcsr3',setup=setup_statements2) 
t2b=experiment_2b.repeat(3,n)
#print(min(t2b)*1000/n)
T2b = min(t2b)*1000/n

#print('2c')
experiment_2c= timeit.Timer(stmt='np.add(Mx,Mx2)',setup=setup_statements2) 
t2c=experiment_2c.repeat(3,n)
#print(min(t1c)*1000/n)
T2c = min(t2c)*1000/n


#print('3a')
experiment_3a= timeit.Timer(stmt='mincsr4.CSR_x_VECTOR(V)',setup=setup_statements3) 
t3a=experiment_3a.repeat(3,n)
#print(min(t3a)*1000/n)
T3a = min(t3a)*1000/n


#print('3b')
experiment_3b= timeit.Timer(stmt='inbygdcsr4.dot(V)',setup=setup_statements3) 
t3b=experiment_3b.repeat(3,n)
#print(min(t3b)*1000/n)
T3b = min(t3b)*1000/n


#print('3c')
experiment_3c= timeit.Timer(stmt='Mx.dot(V)',setup=setup_statements3) 
t3c=experiment_3c.repeat(3,n)
#print(min(t1c)*1000/n)
T3c = min(t3c)*1000/n


index=np.arange(3)
y=[T1a,T1b,T2a,T2b,T3a,T3b]

y1 = [T1a,T2a,T3a]
y2 = [T1b,T2b,T3b]
y3=[T1c,T2c,T3c]

bar_width = 0.25

plt.bar(index-bar_width, y3, bar_width,color="green",label='Utan SM')
plt.bar(index, y1, bar_width,color="blue",label='Eriks',)
plt.bar(index+bar_width, y2, bar_width,color="yellow",label='Inbyggd')

#plt.xlabel('Kod')
plt.ylabel('Tid i ms')
plt.title('Utvärdering av SparseMatrix')

plt.legend()
#plt.tight_layout()
plt.xticks(index + bar_width / 2, ('C-E', 'Add', 'Vector'))
plt.show()
print('Utan SM {}' ' {}' ' {}'.format(T1c,T2c,T3c))
print()
print('Eriks {}' ' {}' ' {}'.format(T1a,T2a,T3a))
print()
print('Inbygd {}' ' {}' ' {}'.format(T1b,T2b,T3b))
