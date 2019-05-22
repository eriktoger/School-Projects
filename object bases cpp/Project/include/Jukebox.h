/**

@file Jukebox.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of Jukebox
*/

#ifndef DT019G_JUKEBOX_H
#define DT019G_JUKEBOX_H

#include <vector>
#include "Album.h"
#include "Menu.h"
#include "Queue.h"
class Jukebox {

public:
    /**
    Constructor
    */
    Jukebox();

    /**
    Starts the virtual jukebox
    */
    void run();

private:
    Menu jukebox;
    Menu file;
    Menu print;
    Menu play;
    std::vector <Album> albums;
    Queue playlist;

    /**
    Prints file menu
    */
    void fileMenu();

    /**
    add Album, from user input
    */
    void addAlbum();

    /**
    Delete album
    */
    void deleteAlbum();

    /**
    Prints file menu
    */
    void printMenu();

    /**
    Prints play menu
    */
    void playMenu();

    /**
    Opens and read albums from file
    */
    void open();

    /**
    Saves albums to file
    */
    void save();

    /**
    Prints one album, specified by input.
    */
    void printOneAlbum();

    /**
    Print all albums and all song, sorted by album name
    */
    void printAllSortedByAlbumName();

    /**
    Print all albums and all song, sorted by album time
    */
    void printAllSortedByTotalTime();

    /**
    Print just the album names, sorted by names
    */
    void printSimpleSortedByAlbumName();

    /**
    Print just the album names, sorted by time
    */
    void printSimpleSortedByTotalTime();

    /**
    Let user pick songs for playlist
    */
    void createPlaylist();

    /**
    Picks songs by random, user decides how many
    */
    void createRandomList();

    /**
    Plays created playlist
    */
    void playPlaylist();

    /**
    Adds a song to the playlist
    @param i, what song to add
    */
    void addSongToPlaylist(const int &i);

    /**
    Lets user chose from the list of songs
    @return the int for the songs chosen
    */
    std::vector <int> chooseSongs();

    /**
    Put all songs in vector
    @return vector of Song-objects
    */
    std::vector <Song> createSongVector();


    /**
    Ask user for list size, for the random playlist
    @param nrOfTracks
    @return the size for the random playlist
    */

    int getSizeForRandomList(const int &nrOfTracks);

    /**
    add song to an album
    @param i, the song to add,
    @param album
    */
    void addSongToAlbum(const int &i, Album &album);

    /**
    Enables a menu
    @param menu
    */
    void enable(Menu &menu);

    /**
    Print all songs in all albums, with index
    */
    void printAllSongs();

    /**
    Erase and remove album
    @param albumIterator
    */
    void eraseRemoveAlbum( std::vector <Album>::iterator albumIterator);

};

/**
Turns a string to all lower case chars
@param s, the string to lower case
*/
std::string makeStringToLower (std::string &s);

/**
Turns a time-object to a string representative
@param time
return string like hh::mm:ss
*/
std::string timeToString(Time time);

/**
Ask for string
@param question
@return string, answer to the question
*/
std::string askForString(const std::string &question);

/**
Ask for int
@param question
@return string, answer to the question
*/
int askForInt(const std::string &question);

/**
prints the songs in an album
@param album
*/
void printSongs(Album album);

/**
Print a song
@param song
*/
void printSong(Song song);

/**
Says that choice is not available
*/
void choiceNotAvailable();


/**
Waits for a keystroke
*/
void waitForInput();

/**
sort by name
@param A B
@return bool
*/

bool sortByName (Album A, Album B);

#endif //DT019G_JUKEBOX_H