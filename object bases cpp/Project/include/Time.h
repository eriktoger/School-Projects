/**

@file Time.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of Time
*/
#ifndef DT019G_TIME_H
#define DT019G_TIME_H

#include <iostream>
class Time {
private:
    int hours;
    int minutes;
    int seconds;
public:

    /**
    Default constructor
    */
    Time();

    /**
    Constructor
     @param totalSeconds
    */
    Time(int totalSeconds);

    /**
    Constructor
     @param newHours
     @paramnewMinutes
     @param newSeconds
    */
    Time(int newHours, int newMinutes, int newSeconds);

    /**
    Overloading +operator
     @param time
     @return the sum of two Time-objects
    */
    Time operator+(const Time &time) const;

    /**
    Overloading +=operator
     @param time
     @return the updated Time-object
    */
    Time operator+=(const Time &time);

    /**
    Overloading <operator
     @param time
     @return true if less else false
    */
    bool operator<(const Time &time) const;

    /**
    Overloading ==operator
     @param time
     @return true if equal else false
    */
    bool operator==(const Time &time) const;

    /**
    get hours
     @return hours
    */
    int getHours() const;

    /**
    get minutes
     @return minutes
    */
    int getMinutes() const;

    /**
    get seconds
     @return seconds
    */
    int getSeconds() const;

    /**
    set hours
     @param newHours
    */
    void setHours(int newHours);

    /**
    set minutes
     @param newMinutes
    */
    void setMinutes(int newMinutes);

    /**
    set seconds
     @param newSeconds
    */
    void setSeconds(int newSeconds);
};

/**
Overloading <<operator
@param os
@param time
@return ostream-object
*/
std::ostream &operator <<( std::ostream &os, const Time &time);

/**
Overloading >>operator
@param is
@param time
@return istream-object
*/
std::istream &operator >>(std::istream &is, Time &time);
#endif //DT019G_TIME_H
