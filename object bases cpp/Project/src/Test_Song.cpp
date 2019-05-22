//
// Created by erik on 2019-02-25.
//

#include "catch.hpp"
#include "Song.h"
#include <fstream>

TEST_CASE("Song get n set"){
    Song song;
    song.setTitle("hej");
    song.setArtist("hej2");

    Time time;
    time.setHours(1);
    time.setMinutes(1);
    time.setSeconds(1);

    song.setLength(time);
    REQUIRE(song.getTitle() == "hej");
    REQUIRE(song.getArtist() =="hej2");
    REQUIRE(song.getLength() == time);

}

TEST_CASE("song << and >>"){
    std::ofstream outfile("songTest.txt");
    Song song;
    song.setTitle("title");
    song.setArtist("artist");
    Time time;
    time.setHours(1);
    time.setMinutes(1);
    time.setSeconds(1);
    song.setLength(time);

    outfile << song;
    outfile.close();

    std::ifstream infile("songTest.txt");
    Song song2;
    infile >> song2;

    REQUIRE(song.getTitle() == song2.getTitle() );
    REQUIRE(song.getArtist() == song2.getArtist() );
    REQUIRE(song.getLength() == song2.getLength() );

    infile.close();

}