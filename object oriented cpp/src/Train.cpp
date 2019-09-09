// Class: Train
// All the trains in simulation.
//

#include "Train.h"
#include <sstream>
#include <constants.h>
#include <Electrical.h>
#include <Diesel.h>
#include <algorithm>
#include <Coach.h>
#include <Sleeping.h>
#include <OpenFreight.h>
#include <CoverdFreight.h>
#include "helpFunctions.h"

//constructor
//Param std::string info, the info of the train
Train::Train(std::string info){

    correct = true;
    std::stringstream ss(info);

    extractTrainNumber(ss);

    extractStations(ss);

    extractTimes(ss);

    extractSpeed(ss);

    extractVehicles(ss);

    if(!correct){
        std:: cout << info << std::endl;
        std::cout<<"Train info incorrect! Train not even "<< TRAIN_LIFE_CYCLE[0] <<std::endl;
    }
    else{
        status = TRAIN_LIFE_CYCLE[0];
    }

}

// Param std::stringstream &ss, containing the info of a train
void Train::extractTrainNumber(std::stringstream &ss){
    std::string token;
    int tokenInt;
    const char DELIM = SPACE;
    getline(ss,token, DELIM ); // trainnumber
    try{
        tokenInt = std::stoi(token);
        trainNumber = tokenInt;
    }
    catch(const std::invalid_argument&){
        correct = false;
    }
}

// Param std::stringstream &ss, containing the info of a train
void Train::extractStations (std::stringstream &ss){
    std::string token;
    const char DELIM = SPACE;

    getline(ss,token, DELIM ); // depature station
    depatureStation = token;

    getline(ss,token, DELIM ); // destination station
    destinationStation = token;
}

// Param std::stringstream &ss, containing the info of a train
void Train::extractTimes(std::stringstream &ss){
    std::string token;
    const char DELIM = SPACE;

    // depature time
    getline(ss,token, DELIM );
    std::size_t found = token.find(COLON);
    std::string hourString = token.substr(0,found);
    std::string minuteString = token.substr(found+1,token.length());

    int hour;
    int minute;
    if(found!=std::string::npos){
        try{
            hour = std::stoi(hourString);
            minute = stoi(minuteString);
            departureTime.setHours( hour);
            departureTime.setMinutes(minute);
            originalDepartureTime.setHours(hour);
            originalDepartureTime.setMinutes(minute);
        }
        catch(const std::invalid_argument&){
            correct = false;
        }

        nextAction = departureTime - BEFORE_ASSEMBLY;
    }
    else{
        correct = false;
    }

    // arrival time
    getline(ss,token, DELIM );
    found = token.find(COLON );
    hourString = token.substr(0,found);
    minuteString = token.substr(found+1,token.length());
    if(found!=std::string::npos){
        try{
            hour = std::stoi(hourString);
            minute = stoi(minuteString);
            arrivalTime.setHours( hour);
            arrivalTime.setMinutes(minute);
            originalArrivalTime.setHours( hour);
            originalArrivalTime.setMinutes(minute);
        }
        catch(const std::invalid_argument&){
            correct = false;
        }
    }
    else {
        correct = false;
    }
}

// Param std::stringstream &ss, containing the info of a train
void Train::extractSpeed(std::stringstream &ss){
    std::string token;
    const char DELIM = SPACE;
    getline(ss,token, DELIM ); // speed
    try{
        int speedInt = std::stoi(token);

        maxSpeed = speedInt;
    }
    catch(const std::invalid_argument&){
        correct = false;
    }
}

// Param std::stringstream &ss, containing the info of a train
void Train::extractVehicles(std::stringstream &ss ){
    std::string token;
    int tokenInt;
    const char DELIM = SPACE;

    while (std::getline(ss,token, DELIM ) ){
        try{
            tokenInt = std::stoi(token);
            vehicleTypes.push_back(tokenInt);
        }
        catch(const std::invalid_argument&){
            correct = false;
        }

    }
}

//Param std::unique_ptr <Vehicle> vehicle, the vehicle that is added
void Train::addVehicle( std::unique_ptr <Vehicle> vehicle){
    vehicle->addToHistory("Train nr: " + std::to_string(trainNumber) );
    vehicles.push_back( std::move (vehicle) );
}

// Return first vehicle in vector
std::unique_ptr <Vehicle> Train::removeVehicle(){
    unsigned int n = 0;
    while(vehicles[n] == nullptr){
        n++;
        if(n > vehicles.size()){

            return nullptr;
        }
    }

    return std::move(vehicles[n]);
}

// creates a mapping so that the first wagon in Trains.txt can be printed first
// even if the train adds wagons in "wrong" order
// but i seems that it was unneccessary because no vehicle is on wrong order
void Train::createMapping(){

    clearMapping();
    long tempAlreadySeen = 0;
    int tempCounter =0;
    for(unsigned  i = 0; i < vehicleTypes.size(); i ++){
        if(i > 0){
            tempAlreadySeen = std::count(vehicleTypes.begin(),vehicleTypes.begin()+i,vehicleTypes[i]);

        }
        else {
            tempAlreadySeen = 0;
        }

        tempCounter = 0;
        for(auto &v : vehicles){

            if(vehicleTypes[i] == v->type() && tempCounter == tempAlreadySeen){
                auto index = std::find_if(vehicles.begin(),vehicles.end(),[&v](std::unique_ptr <Vehicle> &vp ){

                    if(vp->getId() == v->getId()){
                        return true;
                    }
                    return false;
                });
                if (index != vehicles.end()){
                    mapping.push_back(std::distance(vehicles.begin(), index));
                }
                break;
            }
            else if(vehicleTypes[i] == v->type()){
                tempCounter++;
            }

        }
    }
}

//returns lowest speed from the locomotives and the train.
int Train::getLowestSpeed() const{
    int lowestSpeed = 99999;
    int type;
    for( auto &v: vehicles){
        type = v->type();
        if(type == ELECTRICAL) {
            //auto ptr = std::dynamic_cast<Electrical>(v);

            // https://stackoverflow.com/questions/11002641/dynamic-casting-for-unique-ptr?lq=1
            //std::unique_ptr<Electrical> y(dynamic_cast<Electrical*>(v.get()));

            // Im only getting the reference,
            auto derivedElectrical = dynamic_cast<Electrical&>(*v);
            lowestSpeed = std::min(lowestSpeed,derivedElectrical.getSpeed());

        }

        if(type== DIESEL  ){
            auto derivedDiesel = dynamic_cast<Diesel&>(*v);
            lowestSpeed = std::min(lowestSpeed,derivedDiesel.getSpeed());
        }
    }

    lowestSpeed = std::min(lowestSpeed,getMaxSpeed());
    return lowestSpeed;

    }

std::vector <int> Train::getVehiclesAdded() const{
    std::vector <int> addedVehicles;
    for(auto &p : vehicles ){
        addedVehicles.push_back(p->type());
    }
    return addedVehicles;
}

bool Train::hasVehicle(int id){
    for( auto const & v : vehicles){

            if(id == v->getId()){

                return true;
            }
    }
    return false;
}

void Train::eraseNullptr(){

    vehicles.erase(std::remove(vehicles.begin(), vehicles.end(), nullptr), vehicles.end());
}


void Train::printVehicleTypes() const{

    if( !vehicles.empty()){
        std::cout<< "\t" <<"Vehicles:" <<std::endl;
    }

    // should print in the order of vehicletypes
    // deassembled should have empty mapping?
    for( auto  &i :mapping ){
        int type = vehicles[i]->type();

        if(type == COACH) {
            auto derivedCoach = dynamic_cast<Coach&>(*vehicles[i]);
            printCoach(derivedCoach);
        }

        if(type == SLEEPING) {
            auto derivedSleeping = dynamic_cast<Sleeping&>(*vehicles[i]);
            printSleeping(derivedSleeping);

        }

        if(type == OPENFREIGHT) {
            auto derivedOpen = dynamic_cast<OpenFreight&>(*vehicles[i]);
            printOpen(derivedOpen);
        }
        if(type == COVERDFREIGHT) {
            auto derivedCoverd = dynamic_cast<CoverdFreight&>(*vehicles[i]);
            printCoverd(derivedCoverd);
        }
        if(type == ELECTRICAL) {
            auto derivedElectrical = dynamic_cast<Electrical&>(*vehicles[i]);
            printElectrical(derivedElectrical);
        }
        if(type == DIESEL){
            auto derivedDiesel = dynamic_cast<Diesel&>(*vehicles[i]);
            printDiesel(derivedDiesel);
        }
    }

    std::vector <int> vehiclesToAssembly = getVehicleTypes();
    std::vector <int> vehiclesInPlace = getVehiclesAdded();

    //only the wagons that not have been added before shall be added.
    for(auto i : vehiclesInPlace){
        auto it = std::find(vehiclesToAssembly.begin(), vehiclesToAssembly.end(), i);
        vehiclesToAssembly.erase((it));
    }

    if(!vehiclesToAssembly.empty()){
        std::cout <<"\t" <<"Missing vehicles:"<<std::endl;
    }
    for(auto const &i : vehiclesToAssembly){
        std::cout <<"\t\t" << VEHICLE_NAMES[i]<<std::endl;
    }
}

void Train::findVehicle(int id,std::string logLevel) const{

    for(auto const &v: vehicles){
        if( v->getId() == id){
            int type = v->type();

            if(type == COACH){
                auto derivedCoach = dynamic_cast<Coach&>(*v);
                printCoach(derivedCoach);
            }

            if(type == SLEEPING){
                auto derivedSleeping = dynamic_cast<Sleeping&>(*v);
                printSleeping(derivedSleeping);

            }
            if(type == OPENFREIGHT){
                auto derivedOpen = dynamic_cast<OpenFreight&>(*v);
                printOpen(derivedOpen);

            }
            if(type == COVERDFREIGHT){
                auto derivedCoverd = dynamic_cast<CoverdFreight&>(*v);
                printCoverd(derivedCoverd);

            }
            if(type == ELECTRICAL){
                auto derivedElectrical = dynamic_cast<Electrical&>(*v);
                printElectrical(derivedElectrical);

            }
            if(type == DIESEL){
                auto derivedDiesel = dynamic_cast<Diesel&>(*v);
                printDiesel(derivedDiesel);

            }

            if(logLevel == LOG_HIGH){
                printHistory(v->getHistory());
            }
            return;
        }
    }
}