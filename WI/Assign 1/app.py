#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 23 18:40:16 2019

@author: erik
"""

from flask import Flask
from flask_bootstrap import Bootstrap
from flask import render_template
from recommenderSystem import userToMovie, userToUsers, movieToUsers, movieToMovies, userToMoviesIB, init
from flask import request

app = Flask(__name__)
app.config['SECRET_KEY'] = 'd11e4ec86b9f6b2eb256784fa7548b1a'


bootstrap = Bootstrap(app)
@app.route('/' , methods = ['GET','POST'])
@app.route('/home', methods = ['GET','POST'])
def home():
    
    if request.method == 'POST':
        tag = request.form['user']
        method = request.form['type']
        if method == 'userToUsers-Euclid':  
            answer =userToUsers(tag, True)
        elif method == 'userToUsers-Pearson':
            answer = userToUsers(tag, False)
        elif method == 'userToMovies-Euclid':
            answer = userToMovie(tag,True)
        elif method == 'userToMovies-Pearson':
            answer = userToMovie(tag,False)
        elif method =='moviesToUsers-Euclid':
            answer = movieToUsers(tag,True)
        elif method =='moviesToUsers-Pearson':
            answer = movieToUsers(tag,False)
        elif method == 'moviesToMovies-Euclid':
            answer = movieToMovies(tag, True)
        elif method == 'moviesToMovies-Pearson':
            answer = movieToMovies(tag,False)
        elif method == 'userToMoviesIB-euclid':
            answer = userToMoviesIB(tag,True)
        elif method == 'userToMoviesIB-Pearson':
            answer = userToMoviesIB(tag,False)
        
        else:
            answer ="Please try again"
            
        return render_template('calc.html',title='Home', user=tag,answer=answer)
    else:
        return render_template('index.html', title='Home')

if __name__ == '__main__':
    init()
    app.run(debug=True)
    