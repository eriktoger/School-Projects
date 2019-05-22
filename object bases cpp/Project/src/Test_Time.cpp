//
// Created by erik on 2019-02-25.
//
#include "catch.hpp"
#include "Time.h"
#include "Jukebox.h"
#include <fstream>

TEST_CASE("Time add"){
    Time test;
    test.setHours(30);
    test.setMinutes(30);
    test.setSeconds(30);
    Time test2;
    test2.setHours(45);
    test2.setMinutes(45);
    test2.setSeconds(45);
    test = test + test2;

    REQUIRE( test.getHours() == 76);
    REQUIRE( test.getMinutes() == 16);
    REQUIRE( test.getSeconds() == 15);

}

TEST_CASE("Time <"){
    Time test;
    test.setHours(30);
    test.setMinutes(30);
    test.setSeconds(30);
    Time test2;
    test2.setHours(30);
    test2.setMinutes(30);
    test2.setSeconds(31);
    REQUIRE(test < test2);

}

TEST_CASE("Time =="){
    Time test;
    test.setHours(30);
    test.setMinutes(30);
    test.setSeconds(30);
    Time test2;
    test2.setHours(30);
    test2.setMinutes(30);
    test2.setSeconds(30);
    REQUIRE(test == test2);
}


TEST_CASE("Time << and >>"){
    std::ofstream outfile("timeTest.txt");
    Time test;
    test.setHours(30);
    test.setMinutes(30);
    test.setSeconds(30);

    outfile << test;
    outfile.close();

    std::ifstream infile("timeTest.txt");
    Time test2;
    infile >> test2;
    REQUIRE(test == test2);
    infile.close();

}

TEST_CASE("Time >> Wrong format"){
    std::ifstream infile("timeTest2.txt");
    Time test2;
    infile >> test2;
    REQUIRE(infile.fail() );

}

TEST_CASE("Time += operator"){
    Time test;
    test.setHours(30);
    test.setMinutes(30);
    test.setSeconds(30);

    Time test2;
    test2.setHours(30);
    test2.setMinutes(30);
    test2.setSeconds(30);

    Time test3;
    test3.setHours(30);
    test3.setMinutes(30);
    test3.setSeconds(31);

    test += test3;

    REQUIRE(test == (test2 + test3));

}


