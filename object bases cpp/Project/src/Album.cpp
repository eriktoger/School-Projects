/**

@file Album.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of Album
*/
#include "Album.h"
#include <algorithm>

//set name
void Album::setName(std::string const &newName){
    name = newName;
}

//get name
std::string Album::getName() const{
    return name;
}

//get vector of Song-objects
std::vector <Song> Album::getSongs() const{
    return songs;
}

// add song to album
void Album::addSong(Song song){
    songs.push_back(song);
}

//Overload <
bool Album::operator<(const Album &album) const{

    Time time1(0);

    std::for_each(songs.begin(), songs.end(), [&time1] (Song const &song) {
        time1 += song.getLength();
    });


    Time time2(0);

    std::for_each(album.songs.begin(), album.songs.end(), [&time2] (Song const &song) {
        time2 +=  song.getLength();
    });

    return time1 < time2;

}

//Overloading <<operator
std::ostream &operator <<( std::ostream &os, const Album &album){
    os << album.getName() << '\n';
    os << album.getSongs().size() << '\n';

 for(Song const &song : album.getSongs() ){
     os << song << '\n';

 }

 return os;

}

//Overloading >>operator
std::istream &operator >>(std::istream &is, Album &album){
    std::string newName;
    getline(is,newName);

    newName.erase(std::remove(newName.begin(), newName.end(), '\r'),
                  newName.end());

    newName.erase(std::remove(newName.begin(), newName.end(), '\n'),
                  newName.end());
    //with out if( newName.empty()) I hade bad alloc because there is a empty album
    if(newName.empty()){
        return is;
    }

    album.setName(newName);

    int tracks;
    is >> tracks;
    is.ignore(1,'\n');
    std::string tempSong;
    Song song;
    for(int i = 0; i < tracks; i++){
        is >> song;
        album.addSong(song);
        is.ignore(1,'\n');
    }

    return is;

}