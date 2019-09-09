// Class: Simulator
// Runs the simulation and prints the menus
//

#ifndef DT060G_ERTG1700_USERINTEFACE_H
#define DT060G_ERTG1700_USERINTEFACE_H


#include "Station.h"
#include <fstream>
struct Distance{
    std::string city1;
    std::string city2;
    int dist;
};

class Simulator {
private:

    //vectors
    std::vector <Station> stations;
    std::vector <std::string> trips;
    std::vector <Distance> distances;
    std::vector <Train> theTrains;

    //Time
    Time timer = Time(0,0);

    Time interval = STARTING_INTERVAL;
    Time totalDelay = Time(0,0);
    Time startingTime = START_TIME;
    Time endingTime = END_TIME;

    std::string logLevel = LOG_LOW;
    bool showMenu = true;
    bool redo = false; // if true takes you from simulationMenu to startMenu
    int lowestVehicleNr = 9999;
    int highestVehicleNr = 0;
    std::ofstream outFile;

    //creating vectors
    void creatingTrips(std::ifstream &trains);
    void creatingDistances( std::ifstream &trainMap);
    void creatingStationsAndWagons(std::ifstream &trainstations);
    void creatingTheTrains();

    // utility
    bool checkRunningOrArrived();
    void sortTrainsByAction();
    void sortTrainsByTrainNumber();
    void forwardTime(Time intervalInput){timer += intervalInput;};
    void reverseTime(Time intervalInput){timer = timer - intervalInput;};
    Time calculateArrivalTime(Train &tr);
    void calculateAndSetActualSpeed(Train &tr);

    //A trains life cycle and its steps
    void trainLifeCycle(Train &tr);
    void assembleTrain(Train &tr);
    void assembleIncompleteTrain(Train &tr);
    void gettingTrainReady(Train &tr);
    void gettingTrainRunning(Train &tr);
    void trainIsArriving(Train &tr);
    void trainIsFinishing(Train &tr);
    void printStatus(Train const &tr);//prints train after each turn in the lifeCycle

    //Logging
    void logStatus(Train const &tr);
    void logTrain(Train const &tr);

    //Getters
    int getDistance(std::string city1, std::string city2);

    //Menus
    bool startMenu();
    void simulationMenu();
    void trainMenu();
    void stationMenu();
    void vehicleMenu();

    //menu related
    void changeInterval();
    void doNextEvent();
    void changeLogLevel();
    void searchTrainByNumber();
    void printTrain(Train const &tr);
    void printTrainBaseInfo(Train const &tr);
    void searchTrainByVehicleID();
    void searchStationByName();
    void searchVehicleByID();
    void printStatistics();
    void nrOfVehiclesAtStartInStation();
    void trainsThatNeverLeft();
    void delayedTrains();
    void delayedDepartures();

public:
    //Constructor
    Simulator();

    //The simulation
    bool run();

    //End statistics
    void statisticsMenu();

};


#endif //DT060G_ERTG1700_USERINTEFACE_H
