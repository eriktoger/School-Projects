/**

@file Song.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of Song
*/
#ifndef DT019G_SONG_H
#define DT019G_SONG_H

#include <string>
#include <vector>
#include "Time.h"

class Song{

private:
    std::string title;
    std::string artist;
    Time length;

public:

    Song();


    /**
    set title
    @param newTitle
    */
    void setTitle(std::string newTitle);

    /**
    set artist
    @param newArtist
    */
    void setArtist(std::string newArtist);

    /**
    set length
    @param newLength
    */
    void setLength(Time newLength);

    /**
    get title
    @return title
    */

    std::string getTitle() const;

    /**
    get artist
    @return artist
    */
    std::string getArtist() const;

    /**
    get length
    @return length
    */
    Time getLength() const;

    /**
    Overload ==
    @return true if equal, else false
    */
    bool operator ==(const Song &song) const;

};

/**
Overloading <<operator
@param os
@param song
@return ostream-object
*/
std::ostream &operator <<( std::ostream &os, const Song &song);

/**
Overloading >>operator
@param os
@param song
@return ostream-object
*/
std::istream &operator >>(std::istream &is, Song &song);

#endif //DT019G_SONG_H
