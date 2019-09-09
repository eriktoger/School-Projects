// Class: Time
// A simple time class that store hours and minutes
//

#ifndef DT019G_TIME_H
#define DT019G_TIME_H

#include <iostream>
class Time {
private:
    int hours;
    int minutes;
    const int MINUTES_PER_HOUR = 60;
public:

    /**
    Default constructor
    */
    Time();


    /**
    Constructor
     @param newHours
     @paramnewMinutes
     @param newSeconds
    */
    Time(int newHours, int newMinutes);

    /**
    Overloading +operator
     @param time
     @return the sum of two Time-objects
    */
    Time operator+(const Time &time) const;

    Time operator-(const Time &time) const;

    /**
    Overloading +=operator
     @param time
     @return the updated Time-object
    */
    Time operator+=(const Time &time);

    Time operator=(const Time &time);

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
    set hours
     @param newHours
    */
    void setHours(int newHours);

    /**
    set minutes
     @param newMinutes
    */
    void setMinutes(int newMinutes);

    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019
    friend std::ostream& operator<<(std::ostream& os, const Time& time);

};



#endif //DT019G_TIME_H