# -*- coding: utf-8 -*-
"""
Created on Sun Dec 17 14:58:44 2017

@author: erik.toger
"""

import numpy as np

from operator import itemgetter

from scipy.sparse import csr_matrix
from scipy.sparse import csc_matrix
from scipy.sparse import coo_matrix

class SparseMatrix:
    
    ''' Converts a matrix to a CSR-sparsematrix'''
    
    def __init__(self,DATA,TOL=0,TYPE='MX'):
        
        if TYPE =='MX':
            
            self.DATA=DATA # borde denna vara med?
            self.TOL = TOL # borde jag  utöka befogenheterna? t.ex. change element, eller om man ändra TOL så gås hela matrisen igenom? men då måste det kanske vara en method?
            self.shape = DATA.shape
            self.type = TYPE # den hette self.type precis...
            m=DATA.shape[0]
            n=DATA.shape[1]
        
            A = [] # data, appended row by row
            IA=[0] # indptr per row. hur många element finnd det i första raden, i första och andra raden osv. första siffran är 0.
            JA=[] # indices, i vilken kolumn finns datan i list A[]? 
        
            ROWSUM=0

        
            for i in range(m): # borde jag ha self.Mx.shape?
            
                for k in range(n):
                    if abs(DATA[i,k]) > self.TOL:
                        ROWSUM=ROWSUM+1
                        A.append(DATA[i,k])
                        JA.append(int(k))
        
                    else:
                        DATA[i,k]=0
                    
                IA.append(int(ROWSUM))
            
            NNZ=(len(A)) 
            self.number_of_nonzero = NNZ    
            
        
            #IA.append(NNZ) # ska inte detta göras?
            IA=np.array(IA)
            JA=np.array(JA)
            IA.astype(int)
            JA.astype(int)
            self.intern_represent = np.array([np.array(A),IA,JA]) # det är list inne i en array, hur borde det se ut?
            
            """ Gör så att när en def har output i form av en COO-matris
            så tillhör den classen SparseMatriser
            
            """
        if TYPE == 'COO':
            self.number_of_nonzero = len(DATA[0])
            self.intern_represent = np.array([np.array(DATA[0]),np.array(DATA[1],dtype=np.int32),np.array(DATA[2],dtype=np.int32)])
            self.type = TYPE
            
        if TYPE == 'CSR':
            self.number_of_nonzero = len(DATA[0])
            self.intern_represent = np.array([np.array(DATA[0]),np.array(DATA[1],dtype=np.int32),np.array(DATA[2],dtype=np.int32)])
            self.type = TYPE
        
        if TYPE == 'CSC': # denna är inte implementerad 
            self.number_of_nonzero = len(DATA[0])
            self.intern_represent = np.array([np.array(DATA[0]),np.array(DATA[1],dtype=np.int32),np.array(DATA[2],dtype=np.int32)])
            self.type = TYPE
            
            
        
    def __repr__(self):
        return str(self.intern_represent)
        # vill jag ändra denna? ja och jag vill ha det 
        
    
    
    def Change_Element(self,a,i,j): # finns det ett sätt som inte kräver en matris?
        # om jag ändrar ett element som är NZ till NZ så krävs ingen ändring
        
        T=self.CSR_to_COO()
        #print(T.intern_represent)
        J=0
        for k in range(len(T.intern_represent[0])):
            if (i,j) == (T.intern_represent[1][k],T.intern_represent[2][k]):
                T.intern_represent[0][k]=a
                J=1
                new=T.COO_to_CSR()
                
        if J==0:
            A=np.array([a,i,j])
            A.shape= (3,1)
            #print(A)
            #print(T.intern_represent)
            T=np.hstack((T.intern_represent,A))
            #print(T[1])
            #T=sorted(T,key=itemgetter(1,2)) # funkar inte för det är inte triplar
            NEW=[] # borde väl inte vara en lista men orkar inte göra array utan internet
            for i in range(len(T[0])):
                NEW.append([T[0][i],T[1][i],T[2][i]])
            #print(NEW)
            NEW=  sorted(NEW,key=itemgetter(1,2))  
            #print(NEW)
            
            
            
            NEW_C=np.array([(NEW[0])]) # ser till att det blir rätt ordning inför CSR
        
            NEW_C.shape = (3,1)
            for triple in NEW[1:]:
                triple = np.array(triple)
                triple.shape = (3,1)
                NEW_C=np.hstack((NEW_C,triple))
        
        
        
            new=SparseMatrix(NEW_C,TYPE='COO').COO_to_CSR()
        self.intern_represent = new.intern_represent
        self.number_of_nonzero = new.number_of_nonzero
    
    def CSR_to_MATRIX(self):
        
        MX=np.zeros(self.shape)
        
        self.CSR_to_COO()
        for i in range(len(self.intern_represent[0])):
            MX[self.intern_represent[1][i],self.intern_represent[2][i]]=self.intern_represent[0][i]
            
        
        return MX
    
    def CSR_equal_CSC(self,CSC):
       # ändrade precis denna pga arrays kräbde ().all()
        SELFCSC=self.CSR_to_CSC()
        if (CSC.intern_represent[0] == SELFCSC.intern_represent[0]).all() and (CSC.intern_represent[1]== SELFCSC.intern_represent[1]).all() and (CSC.intern_represent[2] == SELFCSC.intern_represent[2]).all(): # varför funkar inte intern_represent, den borde göra nu!
            return True
        else:
            return False
        

    def CSR_to_CSC(self):
        """
        Även denna skapar ju ett nytt object i CSC format.
        finns det något som är beroende av denna?
        så jag bara kan kan ta bort return och ändra self.???
        """
        
        #m=self.shape[0] #row men används visst ej
        n=self.shape[1] # coloumn
        
        A = [] # data, denna gången är den kolumnvis appending
        IA=[0] # indptr, per coloumn, hur många element finns det i första coloumn, i första och andra,
        JA=[] # indices, i vilken rad finns datan?
        B=[] # columnindex of each element in A in correct order 
        SUMofCOL=0
        #number_of_nonzero=0
        columnindex =[]
        ROWind=[] # hur många tal är det i förta raden 
        p=0 # starvärde till att ta fram hur många tal det är i varje rad
        R=0 # rowindex for JA
        RC=0 #rowcount
        RIC=0 #rowindexcount
        """
        Jag parar ihop elementen med sitt columnvärde.
        Sedan ordnar jag dem i rätt ordning ( från CSR är de ju i row, nu ska de var efter column)
        för att sedan ordna rätt indptr (IA).
        Till sist så tar jag reda på vilken rad de finns i.
        self.intern_represent[1] berättar hur många element det finns i första raden. osv
        """
        for i in self.intern_represent[1][1:]:
            ROWind.append(i-p)
            
            p=i
        
        
        
        for i in range(len(self.intern_represent[0])):
            columnindex.append([self.intern_represent[2][i],self.intern_represent[0][i],R])
            RC=RC+1
            if RC==ROWind[RIC]:
                RC=0
                R=R+1
                RIC=RIC+1
        
            
        for i in range(n):
            for TUPLE in columnindex:
                if TUPLE[0]==i:
                    A.append(TUPLE[1])
                    B.append(TUPLE[0])
                    JA.append(TUPLE[2])
                    
        for i in range(n):
            SUMofCOL= SUMofCOL + B.count(i)
            IA.append(SUMofCOL)
        
    
        #self.number_of_nonzero = number_of_nonzero 
        DATA= np.array([A,IA,JA])
        
        return SparseMatrix(DATA,TYPE='CSC')
    
    def CSR_to_CSC_Change(self):
        
        #m=self.shape[0] #row men används visst ej
        n=self.shape[1] # coloumn
        
        A = [] # data, denna gången är den kolumnvis appending
        IA=[0] # indptr, per coloumn, hur många element finns det i första coloumn, i första och andra,
        JA=[] # indices, i vilken rad finns datan?
        B=[] # columnindex of each element in A in correct order 
        SUMofCOL=0
        #number_of_nonzero=0
        columnindex =[]
        ROWind=[] # hur många tal är det i förta raden 
        p=0 # starvärde till att ta fram hur många tal det är i varje rad
        R=0 # rowindex for JA
        RC=0 #rowcount
        RIC=0 #rowindexcount
        """
        Jag parar ihop elementen med sitt columnvärde.
        Sedan ordnar jag dem i rätt ordning ( från CSR är de ju i row, nu ska de var efter column)
        för att sedan ordna rätt indptr (IA).
        Till sist så tar jag reda på vilken rad de finns i.
        self.intern_represent[1] berättar hur många element det finns i första raden. osv
        """
        for i in self.intern_represent[1][1:]:
            ROWind.append(i-p)
            
            p=i
        
        
        
        for i in range(len(self.intern_represent[0])):
            columnindex.append([self.intern_represent[2][i],self.intern_represent[0][i],R])
            RC=RC+1
            if RC==ROWind[RIC]:
                RC=0
                R=R+1
                RIC=RIC+1
        
            
        for i in range(n):
            for TUPLE in columnindex:
                if TUPLE[0]==i:
                    A.append(TUPLE[1])
                    B.append(TUPLE[0])
                    JA.append(TUPLE[2])
                    
        for i in range(n):
            SUMofCOL= SUMofCOL + B.count(i)
            IA.append(SUMofCOL)
        
    
        #self.number_of_nonzero = number_of_nonzero 
        DATA= np.array([A,IA,JA])
        
        self.intern_represent = SparseMatrix(DATA,TYPE='CSC').intern_represent
    
    def CSR_to_COO(self): # borde denna skrivas om? kanske byta ut data mot self och ta bort matrix? kanske bara ha CSR då detta är grunden.

        CSR_A= self.intern_represent[0] # data i ordning efter row
        CSR_IA = self.intern_represent[1] # indptr per row
        CSR_JA = self.intern_represent[2] # indices per coloumn
        DATA_CSR_with_index=[] # ex. [1,2,3] means 1 in row 2 and col 3
        L_CSR_A=len(CSR_A)
        
        
        ROWcounter = 0
        ROWindex = 0
        I = 1
        for i in range(L_CSR_A):
            ROWcounter=ROWcounter+1
            if ROWcounter > CSR_IA[I]:
                ROWindex= ROWindex+1 # efter vi har gått igenom alla tal i row 0 så ökar vi rowindex med 1
                I=I+1 # om vi har flyttat en row så måste vi jämföra med nästa tal
            DATA_CSR_with_index.append([CSR_A[i],ROWindex ,CSR_JA[i]])
            
        OBJECTS = [] # data, appended row by row
        ROW=[] #  datans row
        COL=[] # datans column
        for Object in DATA_CSR_with_index:
            OBJECTS.append(Object[0])
            ROW.append(Object[1])
            COL.append(Object[2])
            
        self.number_of_nonzero = len(CSR_A)

        DATA= np.array([OBJECTS,ROW,COL])
        #self.intern_represent = intern_represent
            
        return SparseMatrix(DATA,TOL=0,TYPE='COO') # kan jag få 
    
    def __add__(self,CSR2):
        A=(self.CSR_to_COO()).intern_represent
        B=CSR2.CSR_to_COO().intern_represent
        C=np.hstack((A,B))
        
        Duplicate=[]
        NEW_C=[]
        for i in range(len(C[0])):
            D=0 # duplicate counter
            for k in range(i+1,len(C[0])):
                if C[1][i]==C[1][k] and C[2][i]==C[2][k]:
                    #print(C[0][i]+C[0][k],C[1][i],C[2][i]) # hur ska göra för att hoppa över den som läggs ihop?
                    NEW_C.append([C[0][i]+C[0][k],C[1][i],C[2][i]])
                    Duplicate.append([C[1][k],C[2][k]])
                    D=1
            if D==0 and [C[1][i],C[2][i]] not in Duplicate:
                NEW_C.append([C[0][i],C[1][i],C[2][i]])
                
        
        NEW_C=sorted(NEW_C,key=itemgetter(1,2))  
        NEW_Cstacked=np.array([(NEW_C[0])]) # ser till att det blir rätt ordning inför CSR
        
        NEW_Cstacked.shape = (3,1)
        for triple in NEW_C[1:]:
            triple = np.array(triple)
            triple.shape = (3,1)
            NEW_Cstacked=np.hstack((NEW_Cstacked,triple))
     
        
        return SparseMatrix(NEW_Cstacked, TYPE='COO').COO_to_CSR()
    
    def COO_to_CSR(self): # det löste inte problemet genom att skapa en static method
        COLind=list(self.intern_represent[1])
        
        SUM=0 # indptr are sums of elements up to that column
        IA=[0]
        for i in range(len(self.intern_represent[0])):
            if COLind.count(i) >0:
                SUM=SUM+COLind.count(i)
                IA.append(SUM)
        
        CSR= np.array([self.intern_represent[0],np.array(IA),self.intern_represent[2]])
        """ varför krävs np.array(IA)? varför blir det inte en matrix av det? 
        
        """

        return SparseMatrix(CSR,TYPE='CSR')
    
    
    
    def CSR_x_VECTOR(self,VECTOR):
         if self.shape[1] != len(VECTOR):
            raise Exception ('vector length does not match number of columns in matrix')
         VECTORanswer= [] # hit kommer svaren landa och bli return value
        
         p=0 #starvärde
         a=0 #startvärde
         for i in self.intern_represent[1][1:]:
             SUM=0
             for k in range(p,int(i)):
                 SUM=SUM+ (self.intern_represent[0][a])*(VECTOR[int(self.intern_represent[2][a])])
                 a=a+1
             VECTORanswer.append(SUM)
             VECTORanswer1 =np.array(VECTORanswer)
             p=i
         #VECTORanswer1.shape= (1,VECTOR.shape[1])    
         return VECTORanswer1 
            




