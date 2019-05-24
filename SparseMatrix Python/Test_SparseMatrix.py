# -*- coding: utf-8 -*-
"""
Created on Mon Dec 25 10:02:57 2017

@author: erik.toger
"""
# %timit s 251 för att testa din kod mot de inbygda

from SparseMatrix import SparseMatrix
import unittest

import numpy as np

import numpy.testing as npt

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

Mx=np.array([(1,8,2),(0,0,3),(0,5,6)])
Mx2=np.array([(0,1,0),(0,2,3),(0,0,6)])

#print(SparseMatrix(Mx))
"""
def test_identity():
    Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
    result=SparseMatrix(Matrix).intern_represent
    print(result)
    
    expected = np.array([[1,1,1],[0,1,2,3],[0,1,2]])
    print(expected[0])
    npt.assert_array_equal(result,expected), 'hej' # funkar inte med hela arrayn, men nu funkar det!
    assert allclose(result[1],expected[1])
    assert allclose(result[2],expected[2])

test_identity()
"""
class TestSparseMatrix(unittest.TestCase):
    def test_init(self):
         Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
         
         result = SparseMatrix(Matrix).intern_represent
         
         expected = np.array([csr_matrix(Matrix).data, csr_matrix(Matrix).indptr, csr_matrix(Matrix).indices])
         
         npt.assert_array_almost_equal(result[0],expected[0])
         npt.assert_array_almost_equal(result[1],expected[1])
         npt.assert_array_almost_equal(result[2],expected[2])
         #npt.assert_array_almost_equal(result,expected) #varför funkar inte denna?
    
    def test_Change_Element(self):
        Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
        M=SparseMatrix(Matrix)
        M.Change_Element(2,0,0)
        MIR=M.intern_represent
        Matrix2=np.array([(2,0,0),(0,1,0),(0,0,1)])
        M2 = SparseMatrix(Matrix2)
        M2IR = M2.intern_represent
        npt.assert_array_almost_equal(MIR[0],M2IR[0])
        npt.assert_array_almost_equal(MIR[1],M2IR[1])
        npt.assert_array_almost_equal(MIR[2],M2IR[2])
        
        Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
        M=SparseMatrix(Matrix)
        M.Change_Element(2,1,0)
        MIR=M.intern_represent
        Matrix2=np.array([(1,0,0),(2,1,0),(0,0,1)])
        M2 = SparseMatrix(Matrix2)
        M2IR = M2.intern_represent
        npt.assert_array_almost_equal(MIR[0],M2IR[0])
        npt.assert_array_almost_equal(MIR[1],M2IR[1])
        npt.assert_array_almost_equal(MIR[2],M2IR[2])
        
    
    def test_CSR_to_MATRIX(self):
        Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
        M=SparseMatrix(Matrix)
        M=M.CSR_to_MATRIX()
        for i in range(M.shape[0]):
            npt.assert_array_almost_equal(Matrix[i],M[i])
            
    def test_CSR_equal_CSC(self):
        
       
        Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
        csr=SparseMatrix(Matrix)
        csc=csr.CSR_to_CSC()
        self.assertTrue(csr.CSR_equal_CSC(csc))
        
        Matrix2=np.array([(2,0,0),(0,2,0),(0,0,2)])
        csr2=SparseMatrix(Matrix2)
        csc2=csr2.CSR_to_CSC()
        self.assertFalse(csr.CSR_equal_CSC(csc2))
      
         
    def test_CSR_to_CSC(self):
        Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
        M=SparseMatrix(Matrix)
        M=M.CSR_to_CSC()
        result=M.intern_represent
        
        expected = np.array([csc_matrix(Matrix).data, csc_matrix(Matrix).indptr, csc_matrix(Matrix).indices])
        
        npt.assert_array_almost_equal(result[0],expected[0])
        npt.assert_array_almost_equal(result[1],expected[1])
        npt.assert_array_almost_equal(result[2],expected[2])
        
    
    def test_CSR_to_CSC_Change(self):
        Matrix=np.array([(1,0,0),(0,1,0),(0,0,1)])
        M=SparseMatrix(Matrix)
        M.CSR_to_CSC_Change()
        M=M.intern_represent
        
        result=M
        expected = np.array([csc_matrix(Matrix).data, csc_matrix(Matrix).indptr, csc_matrix(Matrix).indices])
        
        npt.assert_array_almost_equal(result[0],expected[0])
        npt.assert_array_almost_equal(result[1],expected[1])
        npt.assert_array_almost_equal(result[2],expected[2])
        
        
    def test_CSR_to_COO(self):
        Matrix = np.array([(1,0,0),(0,1,0),(0,0,1)])
        M = SparseMatrix(Matrix)
        result = (M.CSR_to_COO()).intern_represent
        
        
        expected = np.array([coo_matrix(Matrix).data, coo_matrix(Matrix).row, coo_matrix(Matrix).col])
        
        npt.assert_array_almost_equal(result[0],expected[0])
        npt.assert_array_almost_equal(result[1],expected[1])
        npt.assert_array_almost_equal(result[2],expected[2])
        
    def test___add__(self):
        Matrix1 = np.array([(1,0,0),(0,1,0),(0,0,1)])
        Matrix2 = np.array([(0,1,0),(1,0,0),(0,0,1)])
        Matrix3 = np.array([(1,1,0),(1,1,0),(0,0,2)])
        csr1= SparseMatrix(Matrix1)
        csr2= SparseMatrix(Matrix2)
        csr3= SparseMatrix(Matrix3)
        
        result = (csr1+csr2).intern_represent
        expected = csr3.intern_represent
        
        npt.assert_array_almost_equal(result[0],expected[0])
        npt.assert_array_almost_equal(result[1],expected[1])
        npt.assert_array_almost_equal(result[2],expected[2])
        
    def test_COO_to_CSR(self):
        Matrix = np.array([(1,0,0),(0,1,0),(0,0,1)])
        csr = SparseMatrix(Matrix)
        coo = csr.CSR_to_COO()
        coo2 = np.array([coo_matrix(Matrix).data, coo_matrix(Matrix).row, coo_matrix(Matrix).col])
        csr_again = coo.COO_to_CSR()
        
        result = csr_again.intern_represent
        expected = csr.intern_represent
        
        npt.assert_array_almost_equal(result[0],expected[0])
        npt.assert_array_almost_equal(result[1],expected[1])
        npt.assert_array_almost_equal(result[2],expected[2])
        
        result2 = coo.intern_represent
        expected2 = coo2
        
        npt.assert_array_almost_equal(result2[0],expected2[0])
        npt.assert_array_almost_equal(result2[1],expected2[1])
        npt.assert_array_almost_equal(result2[2],expected2[2])
        
    def test_CSR_x_VECTOR(self):
        Matrix = np.array([(1,0,0),(0,1,0),(0,0,1)])
        Mcsr1= SparseMatrix(Matrix)
        Mcsr2=csr_matrix(Matrix)
        V=np.array([1,2,3])
        
        result = Mcsr1.CSR_x_VECTOR(V)
        expected = Mcsr2.dot(V)
        
        npt.assert_array_almost_equal(result,expected)
        
        Matrix2 = np.array([(1,0,0),(0,1,0),(0,0,1)])
        Mcsr3= SparseMatrix(Matrix2)
        V2=V=np.array([1,2,3,4])
        
        self.assertRaises(Exception,Mcsr3.CSR_x_VECTOR,V2 )
        
        # jag vill testa att den raisar 
        
        
        
        
        
        
    
if __name__=='__main__':
    unittest.main()


