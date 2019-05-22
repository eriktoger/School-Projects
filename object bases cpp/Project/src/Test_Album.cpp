//
// Created by erik on 2019-02-26.
//
#include "catch.hpp"
#include "Album.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <ostream>

TEST_CASE("Album << and >> operator"){

    std::ofstream outfile("testAlbum.txt");

    Song song1;
    song1.setTitle("title1");
    song1.setArtist("artist1");
    Time time1(1,1,1);
    song1.setLength(time1);


    Song song2;
    song2.setTitle("title2");
    song2.setArtist("artist2");
    Time time2(2,2,2);
    song2.setLength(time2);

    Song song3;
    song3.setTitle("title3");
    song3.setArtist("artist3");
    Time time3(3,3,3);
    song3.setLength(time3);

    outfile << "album title \n";
    outfile << "3 \n";
    outfile << song1;
    outfile << '\n';
    outfile << song2;
    outfile <<'\n';
    outfile << song3;
    outfile <<'\n';

    outfile.close();


    std::ifstream infile("testAlbum.txt");
    Album album;
    infile >> album;

   std::vector <Song> songs = album.getSongs();
   REQUIRE(songs[0].getTitle() == song1.getTitle() );
   REQUIRE(songs[0].getArtist() == song1.getArtist() );
   REQUIRE(songs[0].getLength() == song1.getLength() );

   REQUIRE(songs[1].getTitle() == song2.getTitle() );
   REQUIRE(songs[1].getArtist() == song2.getArtist() );
   REQUIRE(songs[1].getLength() == song2.getLength() );

   REQUIRE(songs[2].getTitle() == song3.getTitle() );
   REQUIRE(songs[2].getArtist() == song3.getArtist() );
   REQUIRE(songs[2].getLength() == song3.getLength() );

}

TEST_CASE("Album < operator"){
    std::ifstream infile("testAlbum.txt");
    Album album;
    infile >> album;
    infile.close();

    std::ifstream infile2("testAlbum2.txt");
    Album album2;
    infile2 >> album2;
    infile2.close();

    REQUIRE(album < album2);

}