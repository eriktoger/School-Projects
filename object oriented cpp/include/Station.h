// Class: Station
// Is manly responsible for arranging wagons and assemble and deassemble trains
//

#ifndef DT060G_ERTG1700_STATION_H
#define DT060G_ERTG1700_STATION_H

#include <string>
#include "Vehicle.h"
#include "Coach.h"
#include "Sleeping.h"
#include "CoverdFreight.h"
#include "OpenFreight.h"
#include "Electrical.h"
#include "Diesel.h"
#include "Train.h"
#include <vector>
#include <memory>
class Station {
private:
    std::string name;

    // type of vehicles
    std::vector < std::unique_ptr <Coach> > coaches;
    std::vector < std::unique_ptr <Sleeping> > sleepings;
    std::vector < std::unique_ptr <OpenFreight> > openFreights;
    std::vector < std::unique_ptr <CoverdFreight> > coverdFreights;
    std::vector < std::unique_ptr <Electrical> > electricals;
    std::vector < std::unique_ptr <Diesel> > diesels;
    int totalNrOfVehicles = 0;


public:

    //Constructor
    Station(std::string nameInput);

    //assemble and deassemble
    void assembly(Train &train);
    void deassemblyTrain(Train &train);
    void assemblyIncomplete(Train &tr);

    // add wagons
    void addCoach( std::unique_ptr <Coach> vehiclePointer ) {coaches.push_back(std::move(vehiclePointer));}
    void addSleeping( std::unique_ptr <Sleeping> vehiclePointer ) {sleepings.push_back(std::move(vehiclePointer));}
    void addOpenFreight( std::unique_ptr <OpenFreight> vehiclePointer ) {openFreights.push_back(std::move(vehiclePointer));}
    void addCoverdFreight( std::unique_ptr <CoverdFreight> vehiclePointer ) {coverdFreights.push_back(std::move(vehiclePointer));}
    void addElectrical( std::unique_ptr <Electrical> vehiclePointer ) {electricals.push_back(std::move(vehiclePointer));}
    void addDiesel( std::unique_ptr <Diesel> vehiclePointer ) {diesels.push_back(std::move(vehiclePointer));}

    //Getters
    std::string getName()  const  {return name;} ;
    int getTotalNrOfVehicles() const {return totalNrOfVehicles;};

    //other
    void sortWagonsByID();
    void isTrainComplete(Train &train, bool isIncomplete);
    void print(std::string logLevel);
    void findVehicle(int id, std::string logLevel) const;
    void calculateTotalNrOfVehicles();

};


#endif //DT060G_ERTG1700_STATION_H
