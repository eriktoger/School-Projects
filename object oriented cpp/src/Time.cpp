// Class: Time
// A simple time class that store hours and minutes
//

#include "Time.h"
#include "constants.h"
#include <string>

// Default constructor
Time::Time(){
    hours = 0;
    minutes = 0;

}

// Constructor
Time::Time(int newHours, int newMinutes) {
    hours = newHours;
    minutes = newMinutes;

}

// Overloading +operator
Time Time::operator+(const Time &time) const {

    int newMinutes = time.minutes + minutes;
    int newHours = time.hours + hours + (newMinutes / MINUTES_PER_HOUR);

    newMinutes %= MINUTES_PER_HOUR;

    Time sum;
    sum.setHours(newHours);
    sum.setMinutes(newMinutes);

    return sum;
}

Time Time::operator-(const Time &time) const {

    int tempMinutes;
    int tempHours;
    if(time.minutes > minutes){ // lending
        tempHours = hours -1; //what to do if we go minus?
        tempMinutes = minutes + 60;

    }
    else {
        tempMinutes = minutes;
        tempHours = hours;
    }

    int newMinutes = tempMinutes - time.minutes;
    int newHours = tempHours - time.hours;

    Time diff;
    diff.setHours(newHours);
    diff.setMinutes(newMinutes);

    return diff;
}


//Overloading +=operator
Time Time::operator+=(const Time &time){

    minutes += time.getMinutes() ;
    hours += time.getHours() + (minutes / MINUTES_PER_HOUR);

    minutes %= MINUTES_PER_HOUR;

    return *this;
}

// Overloading <operator
bool Time::operator<(const Time &time) const{
    int seconds_1 = 0;
    seconds_1 += hours*MINUTES_PER_HOUR;
    seconds_1 += minutes;


    int seconds_2 = 0;
    seconds_2 += time.hours * MINUTES_PER_HOUR;
    seconds_2 += time.minutes;

    return seconds_1 < seconds_2;

}

// Overloading ==operator
bool Time::operator==(const Time &time) const {
    return  hours == time.hours && minutes == time.minutes;
}

//overloading =
Time Time::operator=(const Time &time){

    minutes = time.getMinutes() ;
    hours = time.getHours() + (minutes / MINUTES_PER_HOUR);

    minutes %= MINUTES_PER_HOUR;

    return *this;
}

//get hours
int Time::getHours() const{
    return hours;
}

// get minutes
int Time::getMinutes() const{
    return minutes;
}


// set hours
void Time::setHours(int newHours) {
    hours = newHours;
}

//set minutes
void Time::setMinutes(int newMinutes) {
    minutes = newMinutes;
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
    std::string days,hours,minutes;

    days += std::to_string (time.getHours() / 24 ) ;
    hours = std::to_string (time.getHours() %24) ;
    minutes = std::to_string(time.getMinutes());

    if(hours.size() == 1){
        hours = "0" + hours;
    }
    if(minutes.size() == 1){
        minutes = "0" + minutes;
    }

    if(days != "0"){
        os << days << ':' << hours<< ':'<<minutes;

    }
    else{
        os << hours<< ':'<<minutes;
    }

    return os;
}