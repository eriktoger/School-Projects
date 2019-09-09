// Class: Station
// Is manly responsible for arranging wagons and assemble and deassemble trains
//

#include "Station.h"
#include "constants.h"
#include <algorithm>
#include <sstream>
#include "helpFunctions.h"

//Constructor
Station::Station(std::string nameInput){
    name = nameInput;
}
// Param Train train that gets assembled
void Station::assembly(Train &train){

    std::vector <int> vehiclesToAssembly = train.getVehicleTypes();
    bool isIncomplete = false;

    sortWagonsByID();

    for (auto i : vehiclesToAssembly){
        switch(i){
            case 0:
                if( !coaches.empty() ){
                    train.addVehicle(std::move(coaches[0]));
                    coaches.erase(coaches.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 1:
                if( !sleepings.empty() ){
                    train.addVehicle(std::move(sleepings[0]));
                    sleepings.erase(sleepings.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 2:
                if( !openFreights.empty() ){
                    train.addVehicle(std::move(openFreights[0]) );
                    openFreights.erase(openFreights.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 3:
                if( !coverdFreights.empty() ){
                    train.addVehicle(std::move(coverdFreights[0]) );
                    coverdFreights.erase(coverdFreights.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 4:
                if( !electricals.empty() ){
                    train.addVehicle( std::move(electricals[0]) );
                    electricals.erase(electricals.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 5:
                if( !diesels.empty() ){
                    train.addVehicle( std::move(diesels[0]) );
                    diesels.erase(diesels.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            default:
                break;

        }
    }
    isTrainComplete(train, isIncomplete);



}

void Station::sortWagonsByID(){

    std::sort(coaches.begin(), coaches.end(), [](std::unique_ptr <Coach> const &a,std::unique_ptr <Coach> const &b) -> bool
    { return a->getId() < b->getId(); } );

    std::sort(sleepings.begin(), sleepings.end(), [](std::unique_ptr <Sleeping> const &a,std::unique_ptr <Sleeping> const &b) -> bool
    { return a->getId() < b->getId(); } );

    std::sort(openFreights.begin(), openFreights.end(), [](std::unique_ptr <OpenFreight> const &a,std::unique_ptr <OpenFreight> const &b) -> bool
    { return a->getId() < b->getId(); } );

    std::sort(coverdFreights.begin(), coverdFreights.end(), [](std::unique_ptr <CoverdFreight> const &a,std::unique_ptr <CoverdFreight> const &b) -> bool
    { return a->getId() < b->getId(); } );

    std::sort(electricals.begin(), electricals.end(), [](std::unique_ptr <Electrical> const &a,std::unique_ptr <Electrical> const &b) -> bool
    { return a->getId() < b->getId(); } );

    std::sort(diesels.begin(), diesels.end(), [](std::unique_ptr <Diesel> const &a,std::unique_ptr <Diesel> const &b) -> bool
    { return a->getId() < b->getId(); } );
}

//Either train stays incomplete or becomes complete
//Param Train train that maybe is completed
//Param bool isIncomplete, checks if the train is complete or not
void Station::isTrainComplete(Train &train, bool isIncomplete){

    if(isIncomplete){
        train.setStatus(TRAIN_LIFE_CYCLE[1]);

        // add 10 minutes to
        train.addToDepartureTime(INCOMPLETE_DELAY);
        train.addToArrivalTime(INCOMPLETE_DELAY);

        train.setLastAction(train.getNextAction());
        train.setNextAction(train.getNextAction() + INCOMPLETE_DELAY);

    }
    else{

        train.setStatus(TRAIN_LIFE_CYCLE[2]);
        train.setLastAction(train.getNextAction());
        train.setNextAction( train.getDepartureTime() - BEFORE_READY);
    }
}

// looks almost like assembly but will only assemble the missing parts
//Param Train train, the incomplete train that gets assembled
void Station::assemblyIncomplete(Train &train){
    std::vector <int> vehiclesToAssembly = train.getVehicleTypes();
    std::vector <int> vehiclesInPlace = train.getVehiclesAdded();

    bool isIncomplete = false;

    //only the wagons that not have been added before shall be added.
    for(auto i : vehiclesInPlace){
        auto it = std::find(vehiclesToAssembly.begin(), vehiclesToAssembly.end(), i);
        vehiclesToAssembly.erase((it));
    }

    sortWagonsByID();

    for (auto i : vehiclesToAssembly){

        switch(i){

            case 0:

                if( !coaches.empty() ){
                    train.addVehicle(std::move(coaches[0]));
                    coaches.erase(coaches.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 1:
                if( !sleepings.empty() ){
                    train.addVehicle(std::move(sleepings[0]));
                    sleepings.erase(sleepings.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 2:
                if( !openFreights.empty() ){
                    train.addVehicle(std::move(openFreights[0]) );
                    openFreights.erase(openFreights.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 3:
                if( !coverdFreights.empty() ){
                    train.addVehicle(std::move(coverdFreights[0]) );
                    coverdFreights.erase(coverdFreights.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 4:
                if( !electricals.empty() ){
                    train.addVehicle( std::move(electricals[0]) );
                    electricals.erase(electricals.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            case 5:
                if( !diesels.empty() ){
                    train.addVehicle( std::move(diesels[0]) );
                    diesels.erase(diesels.begin());
                }
                else{
                    isIncomplete = true;
                }
                break;
            default:
                break;
        }
    }

    isTrainComplete(train,isIncomplete);
}

// when a train enters a station, the vehicles are put in the right bin
//Param Train train, that get deassembled
void Station::deassemblyTrain(Train &train){
    int counter = 0;
    int type;
    long int nrOfVehicles=  train.getVehicleTypes().size();

    while(nrOfVehicles--) {

        std::unique_ptr<Vehicle> vehiclePointer = train.removeVehicle();
        vehiclePointer->addToHistory(name);

        if (vehiclePointer == nullptr || counter > 20) {
            break;
        }

        type = vehiclePointer->type();

        // https://stackoverflow.com/questions/11002641/dynamic-casting-for-unique-ptr?lq=1
        if ( type== COACH) {

            std::unique_ptr<Coach> coach{dynamic_cast<Coach*>(vehiclePointer.release())};
            addCoach(std::move(coach));

        }

        if (type == SLEEPING) {
            std::unique_ptr<Sleeping> sleeping{dynamic_cast<Sleeping*>(vehiclePointer.release())};
            addSleeping(std::move(sleeping));
        }

        if (type == OPENFREIGHT) {

            std::unique_ptr<OpenFreight> openfreight{dynamic_cast<OpenFreight*>(vehiclePointer.release())};
            addOpenFreight(std::move(openfreight));
        }

        if (type == COVERDFREIGHT) {

            std::unique_ptr<CoverdFreight> coverdfreight{dynamic_cast<CoverdFreight*>(vehiclePointer.release())};
            addCoverdFreight(std::move(coverdfreight));
        }

        if (type == ELECTRICAL) {

            std::unique_ptr<Electrical> electrical{dynamic_cast<Electrical*>(vehiclePointer.release())};
            addElectrical(std::move(electrical));

        }

        if (type == DIESEL) {

            std::unique_ptr<Diesel> diesel{dynamic_cast<Diesel*>(vehiclePointer.release())};
            addDiesel(std::move(diesel));
        }
        counter++;
    }

    train.eraseNullptr();
    train.clearMapping();

}

//prints the Station information and at high level vehicle info
//Param std::string logLevel, level of detail that should be printed
void Station::print(std::string logLevel){

    std::cout<<getName()<<std::endl;

    std::cout <<"Number of coaches "<<coaches.size()<<std::endl;
    if(logLevel == LOG_HIGH){
        for(auto const &p: coaches){

            std::cout <<"\t" <<"["<<p->getTypeName()<<"] ";
            std::cout <<"id: "<<p->getId()<<", ";
            std::cout <<p->getNumberOfChairs()<<" seats,";
            if(!p->getInternet()) {
                std::cout << " no";
            }
            std::cout <<" internet onboard."<<std::endl;
        }

    }

    std::cout <<"Number of sleeping wagons "<<sleepings.size()<<std::endl;
    if(logLevel == LOG_HIGH) {
        for (auto const &p: sleepings) {
            std::cout << "\t" << "[" << p->getTypeName() << "] ";
            std::cout << "id: " << p->getId() << ", ";
            std::cout << p->getNumberOfBeds() << " beads." << std::endl;
        }
    }

    std::cout <<"Number of open freights "<<openFreights.size()<<std::endl;
    if(logLevel == LOG_HIGH) {
        for (auto const &p: openFreights) {
            std::cout <<"\t" <<"["<<p->getTypeName()<<"] ";
            std::cout <<"id: "<<p->getId()<<", ";
            std::cout <<"Area "<<p->getArea()<<" m² , ";
            std::cout <<"Capacity "<<p->getCapacity()<<" ton."<<std::endl;
        }
    }

    std::cout <<"Number of coverd freights "<<coverdFreights.size()<<std::endl;
    if(logLevel == LOG_HIGH) {
        for (auto const &p: coverdFreights) {
            std::cout <<"\t" <<"["<<p->getTypeName()<<"] ";
            std::cout <<"id: "<<p->getId()<<", ";
            std::cout <<"Cargo volume "<<p->getCapacity()<<" m³."<<std::endl;
        }
    }

    std::cout <<"Number of electricals "<<electricals.size()<<std::endl;
    if(logLevel == LOG_HIGH) {
        for (auto const &p: electricals) {
            std::cout <<"\t" <<"["<<p->getTypeName()<<"] ";
            std::cout <<"id: "<<p->getId()<<", ";
            std::cout <<"max speed: " << p->getSpeed()<<" km/h, ";
            std::cout <<"power " <<p->getPowerKW()<< "kw."<<std::endl;
        }
    }

    std::cout <<"Number of diesels "<<diesels.size()<<std::endl;
    if(logLevel == LOG_HIGH) {
        for (auto const &p: diesels) {
            std::cout <<"\t" <<"["<<p->getTypeName()<<"] ";
            std::cout <<"id: "<<p->getId()<<", ";
            std::cout <<"max speed: " << p->getSpeed()<<" km/h, ";
            std::cout <<"fuel consumption: " <<p->getFuelUsage()<< "l/h."<<std::endl;
        }
    }

}

//finds and prints a vehicle
//Param int id, what wagon
//Param std::string logLevel, level of detail that should be printed
void Station::findVehicle(int id, std::string logLevel) const{

    //https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
    std::vector <std::string> history;
    for(auto const &p: coaches){
        if(p->getId() == id){
            printCoach(*p);
            if(logLevel ==LOG_HIGH){
                history = p->getHistory();
                printHistory(history);
            }
            return;
        }
    }

    for(auto const &p: sleepings){
        if(p->getId() == id){
            printSleeping(*p);
            if(logLevel ==LOG_HIGH){
                history = p->getHistory();
                printHistory(history);
            }
            return;
        }
    }

    for(auto const &p: openFreights){
        if(p->getId() == id){
            printOpen(*p);
            if(logLevel ==LOG_HIGH){
                history = p->getHistory();
                printHistory(history);
            }
            return;
        }
    }

    for(auto const &p: coverdFreights){
        if(p->getId() == id){
            printCoverd(*p);
            if(logLevel ==LOG_HIGH){
                history = p->getHistory();
                printHistory(history);
            }
            return;
        }
    }

    for(auto const &p: electricals){
        if(p->getId() == id){
            printElectrical(*p);
            if(logLevel ==LOG_HIGH){
                history = p->getHistory();
                printHistory(history);
            }
            return;
        }
    }

    for(auto const &p: diesels){
        if(p->getId() == id){
            printDiesel(*p);
            if(logLevel ==LOG_HIGH){
                history = p->getHistory();
                printHistory(history);
            }
            return;
        }
    }
}

void Station::calculateTotalNrOfVehicles()  {
    totalNrOfVehicles = 0;
    totalNrOfVehicles += coaches.size();
    totalNrOfVehicles += sleepings.size();
    totalNrOfVehicles += openFreights.size();
    totalNrOfVehicles += coverdFreights.size();
    totalNrOfVehicles += electricals.size();
    totalNrOfVehicles += diesels.size();
}