/**

@file Time.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of Time
*/

#include "Time.h"
#include "constants.h"
#include <string>

// Default constuctor
Time::Time(){
    hours = 0;
    minutes = 0;
    seconds = 0;
}

// Constructor
Time::Time(int newHours, int newMinutes, int newSeconds) {
    hours = newHours;
    minutes = newMinutes;
    seconds = newSeconds;

}

// Constructor
Time::Time(int totalSeconds){
    hours = totalSeconds / SECONDS_PER_HOUR;
    totalSeconds %= SECONDS_PER_HOUR;

    minutes = totalSeconds / SECONDS_PER_MINUTE;
    totalSeconds %= SECONDS_PER_MINUTE;

    seconds = totalSeconds;
}

// Overloading +operator
Time Time::operator+(const Time &time) const {

    int newSeconds = time.seconds + seconds;
    int newMinutes = time.minutes + minutes +  (newSeconds / SECONDS_PER_MINUTE) ;
    int newHours = time.hours + hours + (newMinutes / MINUTES_PER_HOUR);

    newSeconds %= SECONDS_PER_MINUTE;
    newMinutes %= MINUTES_PER_HOUR;

    Time sum;
    sum.setHours(newHours);
    sum.setMinutes(newMinutes);
    sum.setSeconds(newSeconds);

    return sum;
}

//Overloading +=operator
Time Time::operator+=(const Time &time){
    seconds += time.getSeconds();
    minutes += time.getMinutes() +  (seconds / SECONDS_PER_MINUTE) ;
    hours += time.getHours() + (minutes / MINUTES_PER_HOUR);

    seconds %= SECONDS_PER_MINUTE;
    minutes %= MINUTES_PER_HOUR;

    return *this;
}

// Overloading <operator
bool Time::operator<(const Time &time) const{
    int seconds_1 = 0;
    seconds_1 += hours * SECONDS_PER_HOUR;
    seconds_1 += minutes * SECONDS_PER_MINUTE;
    seconds_1 += seconds;

    int seconds_2 = 0;
    seconds_2 += time.hours * SECONDS_PER_HOUR;
    seconds_2 += time.minutes * SECONDS_PER_MINUTE;
    seconds_2 += time.seconds;

    return seconds_1 < seconds_2;

}

// Overloading ==operator
bool Time::operator==(const Time &time) const {
    return  hours == time.hours &&
            minutes == time.minutes &&
            seconds == time.seconds;
}

//get hours
int Time::getHours() const{
    return hours;
}

// get minutes
int Time::getMinutes() const{
    return minutes;
}

//get seconds
int Time::getSeconds() const{
    return seconds;
}

// set hours
void Time::setHours(int newHours) {
    hours = newHours;
}

//set minutes
void Time::setMinutes(int newMinutes) {
    minutes = newMinutes;
}

//set seconds
void Time::setSeconds(int newseconds) {
    seconds = newseconds;
}

// Overloading <<operator
std::ostream &operator <<( std::ostream &os, const Time &time){
    int seconds_1 = 0;
    seconds_1 += time.getHours() * MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
    seconds_1 += time.getMinutes() * SECONDS_PER_MINUTE;
    seconds_1 += time.getSeconds();
    std::string secondsAsString = std::to_string(seconds_1);
    os << secondsAsString;

    return os;
}

// Overloading >>operator
std::istream &operator >>(std::istream &is, Time &time){
    int seconds;
    is >> seconds;

    if(is.fail()){
        return is;
    }

    time.setHours( seconds / SECONDS_PER_HOUR );
    seconds %= SECONDS_PER_HOUR;

    time.setMinutes( seconds / SECONDS_PER_MINUTE);
    seconds %= SECONDS_PER_MINUTE;

    time.setSeconds(seconds);

    return is;
}

