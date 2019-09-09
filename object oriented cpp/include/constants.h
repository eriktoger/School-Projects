//
// The constants for the project
//

#ifndef DT060G_ERTG1700_CONSTANTS_H
#define DT060G_ERTG1700_CONSTANTS_H
#include <vector>
#include <string>
#include "Time.h"
const std::vector <std::string> TRAIN_LIFE_CYCLE = {"NOT ASSEMBLED","INCOMPLETE","ASSEMBLED",
                                                  "READY", "RUNNING", "ARRIVED" ,"FINISHED"};

const std::vector <std::string> VEHICLE_NAMES = {"Coach", "Sleeping", "Open Freight",
                                                 "Coverd Freight","Electical locomotive" ,
                                                 "Diesel locomotive"};

const std::string LOG_FILE_NAME = "Trainsim.log";

// Vehicle types
const int COACH = 0;
const int SLEEPING = 1;
const int OPENFREIGHT = 2;
const int COVERDFREIGHT = 3;
const int ELECTRICAL = 4;
const int DIESEL = 5;

//Time Constants
const Time BEFORE_ASSEMBLY = Time(0,30); //big letters
const Time STARTING_INTERVAL = Time(0,10);
const Time START_TIME = Time(0,0);
const Time END_TIME = Time(23,59);
const Time ARRIVED = Time(0,20);
const Time INCOMPLETE_DELAY = Time(0,10);
const Time BEFORE_READY = Time(0,10);
const Time TIME_STEP = Time(0,1);

// Other
const char SPACE =' ';
const char COLON = ':';

//log Level
const std::string LOG_LOW = "Low";
const std::string LOG_HIGH = "High";

#endif //DT060G_ERTG1700_CONSTANTS_H
