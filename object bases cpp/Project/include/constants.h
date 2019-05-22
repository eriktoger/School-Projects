//------------------------------------------------------------------------------
// proj.h Objektbaserad programmering i C++
// This header file is included for structural reasons and may be removed!
//------------------------------------------------------------------------------

/**

@file constants.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief constants
*/

#ifndef DT019G_CONSTANTS_H
#define DT019G_CONSTANTS_H
#include <string>

const int SECONDS_PER_MINUTE = 60;
const int MINUTES_PER_HOUR = 60;
const int SECONDS_PER_HOUR = 3600;
const char DELIM = '|';
const char STRING_DELIM = ',';
const std::string STARS ="****";
const std::string DOT_SPACE = ". ";
const std::string FILENAME_IN = "jukebox.txt";
const std::string FILENAME_OUT ="jukeboxout.txt";
const int QUEUE_STARTING_SIZE = 5;
const int QUEUE_GROWTH = 5;
#endif //DT019G_CONSTANTS_H