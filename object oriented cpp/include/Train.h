// Class: Train
// All the trains in simulation.
//

#ifndef DT060G_ERTG1700_TRAIN_H
#define DT060G_ERTG1700_TRAIN_H
#include <string>
#include <ctime>
#include "iostream"
#include "Vehicle.h"
#include "Time.h"
#include "constants.h"
#include <vector>
#include <memory>
class Train {
private:
    std::string status;
    int trainNumber;

    std::vector < std::unique_ptr <Vehicle> > vehicles; // this should not be in the constructor
    std::vector <int> vehicleTypes;
    std::vector <int> mapping;

    std::string depatureStation;
    std::string destinationStation;

    Time departureTime;
    Time arrivalTime;
    Time originalDepartureTime;
    Time originalArrivalTime;
    Time nextAction;
    Time lastAction;
    int maxSpeed;
    double actualSpeed = 0;
    bool delayed = false;

    bool correct; // is the info to the constructor correct?


    //help functions for the constructor
    void extractTrainNumber(std::stringstream &ss);
    void extractStations (std::stringstream &ss);
    void extractTimes(std::stringstream &ss);
    void extractSpeed(std::stringstream &ss);
    void extractVehicles(std::stringstream &ss );





public:
    //Constructor
    Train(std::string info);

    void addVehicle( std::unique_ptr <Vehicle> vehicle);

    std::unique_ptr <Vehicle> removeVehicle();

    bool hasVehicle(int id);
    void eraseNullptr();
    void printVehicleTypes() const;
    void findVehicle(int id,std::string logLevel) const;
    bool isCorrect() {return correct;};
    void createMapping(); // vehicles is in same order as vehicleTypes
    void clearMapping(){mapping.clear();};

    //returns lowest speed from the locomotives or from the train.
    int getLowestSpeed() const;

    // add Time
    void addToNextAction(Time time){nextAction +=time; };
    void addToDepartureTime(Time time){departureTime += time;};
    void addToArrivalTime(Time time){arrivalTime += time;};

    //Getters
    std::vector <int> getVehicleTypes() const {return vehicleTypes;}
    std::vector <int> getVehiclesAdded() const;
    std::string getStatus() const {return status;};
    std::string getDepartureStation() const {return depatureStation;};
    std::string getDestinationStation() const {return destinationStation;};
    int getMaxSpeed() const {return maxSpeed;};
    double getActualSpeed() const {return actualSpeed;};
    int getTrainNumber()const {return trainNumber;};
    Time getNextAction() const {return nextAction;};
    Time getLastAction() const {return lastAction;};
    Time getDepartureTime() const {return departureTime;};
    Time getArrivalTime()const {return arrivalTime;};
    Time getOriginalArrivalTime() const {return originalArrivalTime;};
    Time getOriginalDepartureTime()const {return originalDepartureTime;};
    bool getDelayed ()const {return delayed;};

    //Setters
    void setNextAction(Time time){nextAction = time;};
    void setLastAction(Time time){lastAction = time;};
    void setArrivalTime(Time time){arrivalTime = time;};
    void setStatus(std::string newStatus) {status = newStatus;};
    void setDelayed(bool newDelayed){delayed = newDelayed;};
    void setActualSpeed(double newActualSpeed){actualSpeed = newActualSpeed;};
};


#endif //DT060G_ERTG1700_TRAIN_H
