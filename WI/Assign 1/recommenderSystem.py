#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 24 08:32:06 2019

@author: erik
"""

import math
import csv # https://realpython.com/python-csv/
import numpy as np

folder = "large" #example, large
filePathUsers = "movies_"+ folder +"/users.csv"
filePathMovies = "movies_"+ folder +"/movies.csv"
filePathRatings = "movies_"+ folder +"/ratings.csv"


'''
Creating the global variables 
'''

def createMatrix(size,filePath):
    matrix = np.zeros((size[0],size[1]))
    with open(filePath) as csv_ratings:
        reader_ratings = csv.reader(csv_ratings, delimiter=';')
        line_count = 0
        for row in reader_ratings:
             if line_count == 0:
                 #ignore first row
                 line_count +=1
             else:
                 r = int(row[0]) -1
                 c = int(row[1]) -1
                 v = float(row[2])
                 matrix[r][c] = v
    return matrix

def getIndex(filePath):
    index =[]
    with open(filePath) as csv_index:
         reader_index = csv.reader(csv_index, delimiter=';')
         line_count = 0
         for row in reader_index:
             if line_count == 0:
                 #ignore first row
                 line_count +=1
             else:
                 index.append(row[1])

    return index

def createSmiliarMovies():
    similiarMoviesEuclid = []
    similiarMoviesPearson = []
    for movie in movies:
        euclid = movieToMovies(movie, True)
        pearson = movieToMovies(movie, False)
        similiarMoviesEuclid.append( (movie, euclid))
        similiarMoviesPearson.append( (movie, pearson))
    
    return similiarMoviesEuclid, similiarMoviesPearson

def init():
    global users
    global movies
    global matrix
    global similiarMoviesEuclid
    global similiarMoviesPearson
    
    users = getIndex(filePathUsers)
    movies = getIndex(filePathMovies)
    size = (len(users) , len(movies) )
    matrix = createMatrix(size,filePathRatings)
    similiarMoviesEuclid, similiarMoviesPearson = createSmiliarMovies()
  
    
'''
Calculations
'''    
def euclidSimilarity(userA, userB):
    sim = 0
    notRated = True
    #print(userA)
    #print(userB)
    #print(len(userA), len(userB))
    #print("A: ",matrix)
    for i in range(len(userA)):
        
        #both must have rated it
        if userA[i] != 0 and userB[i] !=0:
            sim += (userA[i] - userB[i])**2
            notRated = False
    
    if notRated:
        return 0
    inv = 1 / (1+sim)
    return inv

def pearsonSimilarity(userA, userB):
    sum1 = 0
    sum2 = 0
    sum1sq = 0
    sum2sq = 0
    pSum = 0
    n = 0
    for i in range(len(userA)):
        #both must have rated it
        if userA[i] != 0 and userB[i] !=0:
            sum1 += userA[i]
            sum2 += userB[i]
            sum1sq += (userA[i])**2
            sum2sq += (userB[i])**2
            pSum += userA[i] * userB[i]
            n +=1
    if n == 0:
        return 0
    num = pSum - sum1 * sum2 / n
    den = math.sqrt( (sum1sq - sum1**2 /n   )  *(sum2sq - sum2**2 /n   ) )
    if den ==0:
        return 0 # or 1?
    return num / (den)

def calcWSUsers(indexUser,userRatings, similarity):
    
    wsList = []
    #print("similarity: ", similarity)
    for i, rating in enumerate(userRatings):
        if rating == 0: # user havnt seen movie
            column = matrix[:,i]
            ws = sum ( [a*b for a,b in zip(similarity,column)] )
            sim = sum( [a for a,b in zip(similarity,column) if b!=0 ] )
            #print(ws , sim)
            wsList.append( (ws/sim,i) )
            
    return wsList 

def calcWSMovies(indexUser,movieRatings, similarity):
    
    wsList = []
    #print("similarity: ", similarity)
    for i, rating in enumerate(movieRatings):
        if rating == 0: # user havnt seen movie
           row = matrix[i]
           ws = sum ( [a*b for a,b in zip(similarity,row)] )
           sim = sum( [a for a,b in zip(similarity,row) if b!=0 ] )
           #print(ws , sim)
           wsList.append( (ws/sim,i) )
            
    return wsList 


def similarUsers( userA, euclid):
    similarity = []
    allUsers = range(len(users))
   
    for i in allUsers:
        userB = matrix[i]
        if euclid:
            sim = euclidSimilarity(userA, userB)
        else:   
            sim = pearsonSimilarity(userA, userB)
        similarity.append(sim)
    
    return similarity

def similarMovies( movieA, euclid):
    similarity = []
    allMovies = range(len(movies))
    for i in allMovies:
        movieB = matrix[:,i]
        #print(movieB)
        if euclid:
            sim = euclidSimilarity(movieA, movieB)
        else:   
            sim = pearsonSimilarity(movieA, movieB)
            #print("hej")
        #print(sim)
        similarity.append(sim)
    
    return similarity

'''
Input User or Movie
Output recommendations/similarities (Users or Movies)
'''   


def userToUsers(user, euclid):
    if user not in users:
        return "User not found"
    
    indexUser = users.index(user)
    userRatings = matrix[indexUser]
    
    similarity = similarUsers(userRatings, euclid)
    simIndex = list ( zip(similarity, range( len(similarity) )) )
    simIndex.sort(key = getKey, reverse = True)
    
    simUsers = simIndex[:4]
    for pair in simUsers:
       if pair[1] ==indexUser:
           simUsers.remove(pair)
           break
       
    #shouldnt be doing anything   
    simUsers = simUsers[:3]
    answer = []   
    for su in simUsers:
        simUser = users[su[1]]
        nr = truncate(su[0],3)
        answer.append( (simUser,nr) )
    
    return answer

def userToMovie(user,euclid):
    if user not in users:
        return "User not found"
    
    indexUser = users.index(user)
    userRatings = matrix[indexUser]
    
    similarity = similarUsers(userRatings, euclid)
    
    wsList = calcWSUsers(indexUser,userRatings, similarity)
   
    wsList.sort(key = getKey, reverse=True)
   
    top3 = wsList[0:3]
    #print("top 3: ", top3)
    answer = []
    for pair in top3:
        nr = truncate(pair[0],3)
        answer.append ( (movies[pair[1]],nr) )
    
    if not answer:
        return "No recommendations"
    return answer


def movieToUsers(movie, euclid):
     if movie not in movies:
        return "movie not found"
    
     movieIndex = movies.index(movie)
     movieRatings = matrix[:,movieIndex]
     
     similarity = similarMovies(movieRatings, euclid)
     wsList = calcWSMovies(movieIndex,movieRatings, similarity)
     wsList.sort(key = getKey, reverse=True)
   
     top3 = wsList[0:3]
     #print("top 3: ", top3)
     answer = []
     for pair in top3:
         nr = truncate(pair[0],3)
         answer.append ( (users[pair[1]],nr) )
    
     if not answer:
         return "No recommendations"
     return answer

def movieToMovies(movie, euclid):
    if movie not in movies:
        return "User not found"
    
    movieIndex = movies.index(movie)
    movieRatings = matrix[:,movieIndex]
    
    similarity = similarMovies(movieRatings, euclid)
    #print("B: ",similarity)
    simIndex = list ( zip(similarity, range( len(similarity) )) )
    simIndex.sort(key = getKey, reverse = True)
    
    simMovies = simIndex[:10]
    for pair in simMovies:
       if pair[1] ==movieIndex:
           simMovies.remove(pair)
           break
       
    #shouldnt be doing anything   
    simMovies = simMovies[:10]
    #print("top 3: ", simMovies)
    answer = []   
    for su in simMovies:
        simMovie = movies[su[1]]
        nr = truncate(su[0],3)
        answer.append( (simMovie,nr) )
    
    return answer

def userToMoviesIB(user,euclid):
    
    indexUser = users.index(user)
    userRatings = matrix[indexUser]
   
    movieDict = {}
    seenMovies = []
    for i, rating in enumerate(userRatings):
        if rating !=0:
            #print(movies[i], rating)
            if euclid:
                movie = similiarMoviesEuclid[i][0]
                seenMovies.append(movie)
                similarTo = similiarMoviesEuclid[i][1]
            else:
                movie = similiarMoviesPearson[i][0]
                seenMovies.append(movie)
                similarTo = similiarMoviesPearson[i][1]
                
            for aMovie in similarTo:
                name = aMovie[0]
                if name in movieDict:
                    movieDict[name][0] += aMovie[1]
                    movieDict[name][1] += rating*aMovie[1]
                else:
                    movieDict[name] = [0,0]
                    movieDict[name][0] += aMovie[1]
                    movieDict[name][1] += rating*aMovie[1]
    moviesRated = []
    for k in movieDict.keys():
        if k not in seenMovies and movieDict[ k ][0] != 0: # user havnt seen it yet
            normalized = movieDict[ k ][1] / movieDict[ k ][0]
            nr = truncate(normalized,3)
            moviesRated.append( (k,nr))
    
    moviesRated.sort(key = getValue, reverse = True)
    
    if len (moviesRated) > 0 :
        return moviesRated[0:3]
    return "No recommendations"


def userToMoviesUB(user,euclid):
    print("Implement me!")


'''
Helper functions
'''

def getKey(item):
    return item[0]

def getValue(item):
    return item[1]

def truncate(n, decimals=0):
    multiplier = 10 ** decimals
    return int(n * multiplier) / multiplier