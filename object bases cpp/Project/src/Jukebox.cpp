/**

@file main.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Main
*/

#include "Jukebox.h"
#include "Menu.h"
#include "Album.h"
#include "constants.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

//Constructor
Jukebox::Jukebox() {
    jukebox.setHeadline("JUKEBOX");
    jukebox.addItem("File..",true);
    jukebox.addItem("Add an album",false);
    jukebox.addItem("Delete an album",false);
    jukebox.addItem("Print..",false);
    jukebox.addItem("Play..",false);
    jukebox.addItem("Exit",true);

    file.setHeadline("FILE");
    file.addItem("Open",true);
    file.addItem("Save",false);
    file.addItem("Back to main menu", true);

    print.setHeadline("PRINT");
    print.addItem("Print one album",false);
    print.addItem("Print all sorted by album name", false);
    print.addItem("Print all sorted by album total time", false);
    print.addItem("Print simple sorted by album name",false);
    print.addItem("Print simple sorted by album total time",false);
    print.addItem("Back to main menu", false);

    play.setHeadline("PLAY");
    play.addItem("Create a playlist from songs", false);
    play.addItem("Create a random list",false);
    play.addItem("Play list",false);
    play.addItem("Back to main menu",false);
}

//Starts the virtual jukebox
void Jukebox::run(){

    bool again = true;
    while (again) {
        jukebox.printMenuItems();
        switch(jukebox.getMenuChoice())
        {
            case 1: if(jukebox.getMenu()[0].getEnable()){
                        fileMenu();
                    }
                    else{
                    choiceNotAvailable();
                    }

                    break;
            case 2: if(jukebox.getMenu()[1].getEnable()){
                        addAlbum();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 3: if(jukebox.getMenu()[2].getEnable()){
                        deleteAlbum();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 4: if(jukebox.getMenu()[3].getEnable()){
                        printMenu();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 5: if(jukebox.getMenu()[4].getEnable()){
                        playMenu();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 6: again = false;
                    break;
            default: std::cout <<"Error"<<std::endl;
        }
    }
}

//Prints file menu
void Jukebox::fileMenu(){
    bool again = true;
    while (again)
    {
        file.printMenuItems();
        switch(file.getMenuChoice())
        {
            case 1: if(file.getMenu()[0].getEnable()){
                        open();
                    }
                    else{
                        choiceNotAvailable();
                    }
                    //std::cin.ignore(999,'\n');

                    break;
            case 2: if(file.getMenu()[0].getEnable()){
                        save();
                    }
                    else{
                    choiceNotAvailable();
                    }

                    break;
            case 3: again = false;
                break;
            default: std::cout <<"Error"<<std::endl;
        }
    }
}

//add Album, from user input
void Jukebox::addAlbum(){

    std::string albumName = askForString("Enter album name: ");

    std::string albumString;
    auto iterator = find_if(begin(albums), end(albums),[&albumString, &albumName](Album album){
        albumString = album.getName();
        return makeStringToLower(albumString) == makeStringToLower(albumName);
    });

    if(iterator != albums.end()){
        std::cout << "Album already exist"<<std::endl;

        return;
    }

    Album album;
    album.setName(albumName);

    int intTracks = askForInt("Enter nr of tracks: ");

    for(int i = 0; i < intTracks; i++){
        addSongToAlbum(i,album);
    }

    albums.push_back(album);

}

//Delete album
void Jukebox::deleteAlbum(){

    std::string albumName = askForString("Enter album name: ");
    albumName = makeStringToLower(albumName);

    std::string albumString;
    auto albumIterator = std::find_if(albums.begin(), albums.end(),[&] ( Album const& album){
        albumString = album.getName();

        albumString = makeStringToLower(albumString);

        return albumString  == albumName;
    });

    eraseRemoveAlbum( albumIterator);


}

//Prints file menu
void Jukebox::printMenu(){
    bool again = true;
    while (again)
    {
        print.printMenuItems();
        switch(print.getMenuChoice())
        {
            case 1: if(print.getMenu()[0].getEnable()){
                        printOneAlbum();
                    }
                    else{
                    choiceNotAvailable();
                    }

                    break;
            case 2: if(print.getMenu()[1].getEnable()){
                        printAllSortedByAlbumName();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 3: if(print.getMenu()[2].getEnable()){
                        printAllSortedByTotalTime();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 4: if(print.getMenu()[3].getEnable()){
                        printSimpleSortedByAlbumName();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 5: if(print.getMenu()[4].getEnable()){
                        printSimpleSortedByTotalTime();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 6: again = false;
                break;
            default: std::cout <<"Error"<<std::endl;
        }
    }
}

//Prints play menu
void Jukebox::playMenu(){
    bool again = true;
    while (again)
    {
        play.printMenuItems();
        switch(play.getMenuChoice())
        {
            case 1: if(play.getMenu()[0].getEnable()){
                        createPlaylist();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 2: if(play.getMenu()[1].getEnable()){
                        createRandomList();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 3: if(play.getMenu()[2].getEnable()){
                        playPlaylist();
                    }
                    else{
                        choiceNotAvailable();
                    }

                    break;
            case 4: again = false;
                break;
            default: std::cout <<"Error"<<std::endl;
        }
    }
}

//Opens and read albums from file
void Jukebox::open(){

    std::ifstream infile(FILENAME_IN);

    if(infile.good()){
        albums.clear();
    }
    else{
        std::cout <<"File not found"<<std::endl;
        return;
    }

    while( !infile.eof() ){

        Album album;
        infile >> album;
        // looks like an empty album is added
        if(!album.getName().empty()){
            albums.push_back(album);
            std::cout <<  album.getName() << " added"<< std::endl;
        }
    }

    if( !albums.empty()){
        enable(jukebox);
        enable(print);
        enable(file);
        enable(play);
    }
    else{
        std::cout << "no albums added" << std::endl;
    }
}

//Saves albums to file
void Jukebox::save(){
    std::ofstream outfile(FILENAME_OUT);

    std::for_each(albums.begin(),albums.end(),[&outfile](const Album &album){
        outfile << album.getName();
        outfile << '\n';
        outfile << album.getSongs().size();
        outfile << '\n';
        auto songs = album.getSongs();
        for(Song &song : songs){
            outfile << song;
            outfile << '\n';
        }
    });

    std::cout << "saved to file: " << FILENAME_OUT <<std::endl;
}

//Prints one album, specified by input.
void Jukebox::printOneAlbum(){

    std::string albumName = askForString("Enter album name: ");
    albumName = makeStringToLower(albumName);

    std::string albumString;
    auto albumIterator = std::find_if(albums.begin(), albums.end(),[&] ( Album const& album){
        albumString = album.getName();
        albumString = makeStringToLower( albumString );
        return albumString  == albumName;
    });

    if(albumIterator != albums.end()){
        Album album = *albumIterator;
        std::cout << album.getName()<<std::endl;
        printSongs(album);
    }
    else{
        std::cout <<"Album not found"<<std::endl;
    }

}

//Print all albums and all song, sorted by album name
void Jukebox::printAllSortedByAlbumName(){

    std::cout << STARS<< " Albums by name, and their songs " << STARS<< std::endl;
    sort( albums.begin( ), albums.end( ), sortByName);

    std::for_each(albums.begin( ), albums.end( ),[](const Album& album){
        std::cout << album.getName() << std::endl;
        printSongs(album);
    } );
}

//Print all albums and all song, sorted by album time
void Jukebox::printAllSortedByTotalTime(){


    std::cout << STARS<< " Albums by time, and their songs " << STARS<< std::endl;
    sort( albums.begin( ), albums.end( ), [ ]( const Album& album1, const Album& album2 )
    {
        return album2 < album1;
    });

    std::for_each(albums.begin( ), albums.end( ),[](const Album& album){
        std::cout << album.getName() << std::endl;
        printSongs(album);
    } );

}

//Print just the album names, sorted by names
void Jukebox::printSimpleSortedByAlbumName(){

    std::cout << STARS<< " Albums by name " << STARS<< std::endl;
    sort( albums.begin( ), albums.end( ), sortByName);

    std::for_each(albums.begin( ), albums.end( ),[](const Album& album){
        std::cout << album.getName()<<std::endl;
    } );
}

//Print just the album names, sorted by time
void Jukebox::printSimpleSortedByTotalTime(){

    std::cout << STARS << " Albums by time " << STARS << std::endl;
    sort( albums.begin( ), albums.end( ), [ ]( const Album& album1, const Album& album2 )
    {
        return album2 < album1;
    });


    std::for_each(albums.begin( ), albums.end( ),[](const Album& album){

        Time time(0,0,0);
        for(const Song &song : album.getSongs()){
            time += song.getLength();
        }

        std::cout << album.getName() << " " <<  timeToString(time) <<  std::endl;

    } );
}

//Let user pick songs for playlist
void Jukebox::createPlaylist() {

    playlist.reset(); // delete the old playlist

    printAllSongs();

    std::vector <int> playlistVector = chooseSongs();

    for(int i: playlistVector) {
        addSongToPlaylist(i);
    }
}

//Picks songs by random, user decides how many
void Jukebox::createRandomList(){

    playlist.reset(); // delete the old playlist

    std::vector <Song> songs = createSongVector();

    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

    std::shuffle(begin(songs),end(songs),rng);

    const int nrOfTracks = songs.size();
    const int sizeOfRandomList = getSizeForRandomList(nrOfTracks);

    for(int i = 0;i < sizeOfRandomList; i++){
        playlist.enque(songs[i]);
    }
}



//Plays created playlist
void Jukebox::playPlaylist(){
    Queue copyQueue = playlist;

    while( !copyQueue.isEmpty() ){
        std::cout << "Playing: ";
        printSong ( copyQueue.deque() );

        // https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program/158614
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

}

//Enables a menu
void Jukebox::enable(Menu & menu){
    menu.enable();

}

//Turns a string to all lower case chars
std::string makeStringToLower (std::string &s){
    std::string toLowerString;
    for(char c : s){
        toLowerString += tolower(c);
    }
    return toLowerString;
}

//Turns a time-object to a string representative
std::string timeToString(Time time){
    std::string timeString;
    int hours = time.getHours();
    int minutes = time.getMinutes();
    int seconds = time.getSeconds();

    if(hours > 0){
        timeString += std::to_string(hours);
        timeString +=':';
    }

    timeString += std::to_string(minutes);
    timeString +=':';

    if(seconds < 10){
        timeString+= '0';
    }

    timeString += std::to_string(seconds);

    return timeString;
}

//prints the songs in an album
void printSongs(Album album){
    auto songs = album.getSongs();
    for_each(songs.begin(), songs.end(), [] (const Song& song){
       printSong(song);
    } );
    std::cout << '\n';
}

//Print a song
void printSong(Song song){
    std::cout << song.getTitle();
    std::cout << " - ";
    std::cout << song.getArtist();
    std::cout << " - ";
    std::cout << timeToString(song.getLength() );
    std::cout << '\n';
}

//Says that choice is not available
void choiceNotAvailable(){
    std::cout << "Choice not avalible, yet"<< std::endl;
}

//Put all songs in vector
std::vector <Song> Jukebox::createSongVector(){
    std::vector < Song> songs;
    for(const Album &album : albums){
        for(const Song &song : album.getSongs()){
            songs.push_back (song);
        }
    }
    return songs;
}

//Print all songs in all albums, with index
void Jukebox::printAllSongs(){

    int songIndex = 1;
    for(const Album &album : albums){
        for(const Song &song : album.getSongs()){
            std::cout << songIndex << " ";
            printSong(song);
            songIndex++;
        }
    }

}

// Lets user chose from the list of songs
std::vector <int> Jukebox::chooseSongs(){
    std::string playlistString;
    std::cout << "What song do you want in your playlist? " << std::endl;
    std::cout << "Enter: 2,10,23  to choose these three songs" << std::endl;

    std::cin.ignore();
    getline(std::cin,playlistString);
    std::istringstream is (playlistString);
    std::vector <int> playlistVector;
    std::string songString;

    while( getline(is,songString, STRING_DELIM ) ){
        try {
            playlistVector.push_back( stoi(songString));
        }
        catch (std::invalid_argument &err) {
            std::cout << "there was an error with: " << err.what() << std::endl;
        }
    }
    return playlistVector;
}

//Adds a song to the playlist
void Jukebox::addSongToPlaylist(const int &i){
    int matchCounter = 1;
    bool found = false;

    // for each song I look through the albums and their songs.

    for (const Album &album : albums) {
        for (const Song &song : album.getSongs()) {

            if ( i == matchCounter) {
                matchCounter++;
                playlist.enque(song);
                found = true;
                break;
            }
            matchCounter++;
        }
        if(found){
            break;
        }
    }
}
//Ask user for list size, for the random playlist
int Jukebox::getSizeForRandomList(const int &nrOfTracks){
    int size = -1;
    while(std::cin.fail() || size > nrOfTracks || size < 0 ){
        std::cin.clear();
        std::cin.ignore(999,'\n');
        std::cout <<"How many random tracks do you want? "<<std::endl;
        std::cout << "Max is: " << nrOfTracks<<std::endl;
        std::cin >> size;
    }
    return size;
}

//Ask for string
std::string askForString(const std::string &question){
    std::string answer;
    std::cin.ignore();
    std::cout << question;
    getline(std::cin,answer);
    return answer;
}

//Ask for int
int askForInt(const std::string &question){
    std::string tracks;

    int intTracks;
    while(true){
        std::cout << question;
        getline(std::cin,tracks);
        try {
            intTracks= stoi(tracks);
            break;
        }
        catch (std::invalid_argument &err) {
            std::cout << "there was an error with: " << err.what() << std::endl;
        }
    }
    return intTracks;

}

//add song to an album
void Jukebox::addSongToAlbum(const int &i,Album &album) {
    std::string artist;
    std::string songName;
    std::string time;

    std::cout <<"track nr "<< i+1<<std::endl;
    std::cout << "Enter artist: ";
    getline(std::cin,artist);

    std::cout << "Enter song title: ";
    getline(std::cin,songName);

    int intTime;
    while(true){
        std::cout << "Enter song length: ";
        getline(std::cin,time);
        try {
            intTime = stoi(time);
            break;
        }
        catch (std::invalid_argument &err) {
            std::cout << "there was an error with: " << err.what() << std::endl;
        }
    }

    Song song;
    song.setTitle(songName);
    song.setArtist(artist);

    Time timeObject;
    timeObject.setHours( intTime / SECONDS_PER_HOUR );
    intTime %= SECONDS_PER_HOUR;

    timeObject.setMinutes(intTime / SECONDS_PER_MINUTE);
    intTime %= SECONDS_PER_MINUTE;

    timeObject.setSeconds(intTime);
    song.setLength(timeObject);

    album.addSong(song);
}

// Erase and remove the album
void Jukebox::eraseRemoveAlbum( std::vector <Album>::iterator albumIterator){
    if(albumIterator != albums.end()){

        Album album = *albumIterator;
        albums.erase(std::remove_if(albums.begin(), albums.end(), [&album](Album &a){
            return a.getName() == album.getName();
        }), albums.end());

        std::cout << album.getName() << "  " <<"deleted"<< std::endl;
    }
    else{
        std::cout <<"Album not found"<<std::endl;
    }
}

// sort by name
bool sortByName (Album A, Album B){

    std::string stringA = A.getName();
    std::string stringB = B.getName();

    stringA = makeStringToLower(stringA);
    stringB = makeStringToLower(stringB);

    return stringA < stringB;
}
// Waits for a keystroke
void waitForInput(){
    std::cout <<"Press enter to continue: ";

    //put this before in the nedded cases
    //std::cin.ignore(999,'\n');
    std::string dummy;
    getline(std::cin,dummy);
    std::cout <<dummy<<std::endl;
    //while(std::cin.get() !='\n' );

    std::cout << "\n \n";
}
