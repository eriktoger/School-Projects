/**

@file Song.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of Song
*/
#include "Song.h"
#include "constants.h"


Song::Song(){
    title = "";
    artist  = "";
    Time time;
    length = time;
}

//set title
void Song::setTitle(std::string newTitle){
    title = newTitle;
}

// set artist
void Song::setArtist(std::string newArtist){
    artist = newArtist;
}

// set length
void Song::setLength(Time newLength){
    length = newLength;
}

// get title
std::string Song::getTitle() const{
    return  title;
}

//get artist
std::string Song::getArtist() const{
    return artist;
}

//get length
Time Song::getLength() const{
    return length;
}

//Overload ==
bool Song::operator ==(const Song &song) const{
    return (title == song.getTitle() ) && (artist == song.getArtist() ) && (length == song.getLength()) ;
}

// Overload <<
std::ostream &operator <<( std::ostream &os, const Song &song){
    os << song.getTitle() << DELIM;
    os << song.getArtist() << DELIM;
    os << song.getLength();

    return os;
}

// Overload >>
std::istream &operator >>(std::istream &is, Song &song){
    std::string title;
    getline(is,title,DELIM);
    song.setTitle(title);

    std::string artist;
    getline(is,artist,DELIM);
    song.setArtist(artist);

    Time length;
    is >> length;
    song.setLength(length);

    return is;
}