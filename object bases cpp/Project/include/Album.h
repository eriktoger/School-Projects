/**

@file Album.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of Album
*/
#ifndef DT019G_ALBUM_H
#define DT019G_ALBUM_H

#include <string>
#include <vector>
#include "Song.h"

class Album{
private:
    std::string name;
    std::vector <Song> songs;

public:
    /**
    add song to album
    @param song
    */
    void addSong(Song song);

    /**
    Overload <
    @param album
    @return true if less else false
    */
    bool operator<(const Album &album) const;

    /**
    set name
    @param newName
    */
    void setName(std::string const &newName);

    /**
    get name
    @return name
    */
    std::string getName() const;

    /**
    get vector of Song-objects
    @return vector of Song-objects
    */
    std::vector <Song> getSongs() const;
};
/**
Overloading <<operator
@param os
@param album
@return ostream-object
*/
std::ostream &operator <<( std::ostream &os, const Album &album);
/**
Overloading >>perator
@param is
@param album
@return istream-object
*/
std::istream &operator >>(std::istream &is, Album &album);

#endif //DT019G_ALBUM_H
