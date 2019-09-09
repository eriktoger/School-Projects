// Class: Simulator
// Runs the simulation and prints the menus
//

#include "Simulator.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "helpFunctions.h"

//Constructorr
//Opens and read 3 files
Simulator::Simulator(){

    //Open files
    std::ifstream trainMap("TrainMap.txt");
    std::ifstream trains("Trains.txt");
    std::ifstream trainstations("TrainStations.txt");

    if(!trainMap.is_open() || !trains.is_open() || !trainstations.is_open() ){
        std:: cout <<"error" <<std::endl;
    }

   outFile.open(LOG_FILE_NAME);

    //Reading trains to trips
    creatingTrips(trains);

    //Reading trainMap to distances
    creatingDistances( trainMap);

    //Reading trainstations and creating Stations and wagons
    creatingStationsAndWagons(trainstations);

    //converting trips to trains
    creatingTheTrains();

}

//Reading trains to trips
void Simulator::creatingTrips(std::ifstream &trains){
    std::string line;
    while(getline(trains,line)){
        // should this be queue instead?
        trips.push_back(line);
    }
}

//Reading trainMap to distances
void Simulator::creatingDistances( std::ifstream &trainMap){
    const char DELIM = ' ';
    std::string line,word1,word2, word3;
    int distance;
    while(getline(trainMap,line)){
        std::stringstream ss(line);

        getline(ss,word1,DELIM);
        getline(ss,word2,DELIM);
        getline(ss,word3,DELIM);
        //std::cout <<word3 << std::endl;
        distance = stoi(word3);
        Distance temp;
        temp.city1 = word1;
        temp.city2 = word2;
        temp.dist =distance;
        distances.push_back(temp);
    }
}
//Reading trainstations and creating Stations and wagons
// the file has Station names and Wagons
// Extract the Station name and put in stations
// Extract a Wagon that belong to that station
// put the Wagons in stations vector for that Wagon type
// Repeat until all Wagons for that station are done
// Repat with next Station
void Simulator::creatingStationsAndWagons(std::ifstream &trainstations){
    char c;
    std::string word;
    std::string number;
    int counter = 0;
    int vehiclenumber =0;
    int type = 0;
    int param0 = 0;
    int param1 = 0;
    int stationNumber = -1;
    std::string currentStation;
    while(trainstations.get(c)){

        if (isalpha(c) || c == '.' || c=='-' ){
            word += c;

        }
        else{

            if (word.length() > 0){
                Station station(word);
                stations.push_back(std::move(station));
                currentStation = word;
                stationNumber++;
                word ="";
                counter = 0;
            }
        }

        if(isdigit(c)){
            number += c;
        }

        if( (c == ' ' || c== ')') && number.length() >0 ) {

            switch(counter%4){
                case 0:
                    vehiclenumber = stoi(number);
                    lowestVehicleNr = std::min(vehiclenumber,lowestVehicleNr);
                    highestVehicleNr = std::max(vehiclenumber, highestVehicleNr);
                    break;
                case 1:
                    type =  stoi(number);
                    break;
                case 2:
                    param0 = stoi(number);
                    break;
                case 3:
                    param1 = stoi(number);
                    break;
                default:
                    break;
            }
            counter++;
            number= "";
        }

        if (c == ')'){
            counter = 0;
            // http://www.drdobbs.com/cpp/c11-uniqueptr/240002708
            if( type == COACH){
                std::unique_ptr <Coach> coach(new Coach(vehiclenumber,param0,param1) ) ;
                coach->addToHistory(currentStation);
                stations[stationNumber].addCoach( std::move(coach));
            }

            if( type == SLEEPING){
                std::unique_ptr <Sleeping> sleeping(new Sleeping(vehiclenumber,param0) ) ;
                sleeping->addToHistory(currentStation);
                stations[stationNumber].addSleeping( std::move(sleeping));
            }

            if( type == OPENFREIGHT){
                std::unique_ptr <OpenFreight> openfreight(new OpenFreight(vehiclenumber,param0,param1) ) ;
                openfreight->addToHistory(currentStation);
                stations[stationNumber].addOpenFreight( std::move(openfreight));
            }

            if( type == COVERDFREIGHT){
                std::unique_ptr <CoverdFreight> coverdFreight(new CoverdFreight(vehiclenumber,param0) ) ;
                coverdFreight->addToHistory(currentStation);
                stations[stationNumber].addCoverdFreight( std::move(coverdFreight));
            }

            if( type == ELECTRICAL){
                std::unique_ptr <Electrical> electrical(new Electrical(vehiclenumber,param0,param1) ) ;
                electrical->addToHistory(currentStation);
                stations[stationNumber].addElectrical( std::move(electrical));
            }

            if( type == DIESEL){
                std::unique_ptr <Diesel> diesel(new Diesel(vehiclenumber,param0,param1) ) ;
                diesel->addToHistory(currentStation);
                stations[stationNumber].addDiesel( std::move(diesel));
            }

        }

    }

    //should this be done later as well?
    //if so we need to save it to startNrOfVehicles  for each s
    for(auto  &s: stations){
        s.calculateTotalNrOfVehicles();
    }
}

//Constructs the train from the trips-info and put it in theTrains
void Simulator::creatingTheTrains(){
    for(auto const &trip : trips){
        Train train(trip);
        if(train.isCorrect()){
            theTrains.push_back(std::move(train));
        }
    }
}

// Shows the Start menu
// Shows Simulation menu
// The Simulation runs for 24 hours or until all trains are finished
// Returns true if user need to go back to startMenu.
bool Simulator::run() {

    redo = false;
    bool runSimulation = startMenu();

    if(!runSimulation){
        return false;
    }

    bool RunningOrArrived = false;
    sortTrainsByAction();
    Time tempTime = interval + Time(0,1);
    Time tempTimer = Time(0,0);
    while(timer < endingTime || RunningOrArrived ) {
        tempTimer = timer;
        if( (startingTime < timer || startingTime == timer) && showMenu && (interval < tempTime) ){
            tempTime = Time(0,1);
            simulationMenu();
            std::cout <<std::endl;
            std::cout <<"Current time " << timer<< std::endl;
            std::cout <<std::endl;

            // if true takes you from simulationMenu to startMenu
            if(redo){
                return true;
            }
        }

        for (auto &tr: theTrains) {

            if ( (tr.getNextAction() < (tempTimer) ) || (tr.getNextAction() == (tempTimer) )  ) {

                trainLifeCycle(tr);

            } // end  timer
            else {
                break; // no need to look further ahead
            }

        } // end for the Trains


        //updating timer
        forwardTime(TIME_STEP);
        tempTime += TIME_STEP;

        sortTrainsByAction();

        //if no trains are running/is arrived and 24 hours has passed
        // the Simulation should end

        RunningOrArrived = checkRunningOrArrived();


    }

    sortTrainsByTrainNumber();


    //should this be after run? i main?depends on Awais anser
    //statisticsMenu();

    return false;
}

//Checking if there are any trains running or just arrived
// the simulation will not stop until all running/arrived trains are taken care of
// Returns true if there is a running/arrived train
bool Simulator::checkRunningOrArrived(){

    for(const auto &t : theTrains){
        std::string status = t.getStatus();
        if(status == TRAIN_LIFE_CYCLE[4] || status == TRAIN_LIFE_CYCLE[5]  ){
            return true;
        }
    }
    return false;

}

// Calculate the arrival time for trains that departs late
//Param Train &tr the train that we calulate
// Return the arrival time
Time Simulator::calculateArrivalTime( Train &tr){

    double lowestSpeed = tr.getLowestSpeed();

    double distance = getDistance(tr.getDepartureStation(),tr.getDestinationStation());
    double timeToTravel = distance / lowestSpeed;

    int hourToTravel = static_cast<int>( timeToTravel);
    int minuteToTravel =  static_cast<int> ( round( (timeToTravel - hourToTravel)*60 ) );

    Time optimalTime = Time(tr.getDepartureTime().getHours(),tr.getDepartureTime().getMinutes()) +
                Time( hourToTravel, minuteToTravel) ;

    Time arrival = std::max(optimalTime, tr.getOriginalArrivalTime() );

    //return tr.getArrivalTime(); // this will take me to the B-grade with perfect results
    return arrival;
}

//A trains lifeCyle is:
//not Assamble, Assemble/Incomplete, Ready, Running, Arrived and Finished.
//The train is check were on its lifeCycle it is and if its ready to move to
//the next phase.
//Param Train &tr is the train that are taking a step in the life cycle
void Simulator::trainLifeCycle(Train &tr) {

    std::string tempStatus = tr.getStatus();

    //Not assambled to Assemble or incomplete
    if(tempStatus == TRAIN_LIFE_CYCLE[0] && (timer < endingTime || timer == endingTime) ) {
        assembleTrain(tr);
        printStatus(tr);
        logStatus(tr);
    }



    //Incomplete to assembled or still incomplete
    if(tempStatus ==TRAIN_LIFE_CYCLE[1] && (timer < endingTime || timer == endingTime) ) {
        //if commented out perfect result for grade C
        assembleIncompleteTrain(tr);
        printStatus(tr);
        logStatus(tr);
    }
    // assembled to ready
    if(tempStatus == TRAIN_LIFE_CYCLE[2]){
        gettingTrainReady(tr);
        printStatus(tr);
        logStatus(tr);
    }

    // ready to running
    if(tempStatus == TRAIN_LIFE_CYCLE[3]){
        gettingTrainRunning(tr);
        printStatus(tr);
        logStatus(tr);
    }

    //Running to Arrived
    if(tempStatus == TRAIN_LIFE_CYCLE[4]){
        trainIsArriving(tr);
        printStatus(tr);
        logStatus(tr);
    }

    // Arrived to Finished
    // Update totalDelay and setDelayed to true
    if(tempStatus == TRAIN_LIFE_CYCLE[5]) {
        trainIsFinishing(tr);
        printStatus(tr);
        logStatus(tr);
        
        //if delayed
        if( Time(0,0) < (tr.getArrivalTime() - tr.getOriginalArrivalTime()) ){
            totalDelay += (tr.getArrivalTime() - tr.getOriginalArrivalTime());
            tr.setDelayed(true);
        }
    }
}
// Param Train &tr is the train that gets assembled
void Simulator::assembleTrain( Train &tr){

    //searching all stations to see where the train is
    for (auto &s : stations) {

        if (tr.getDepartureStation() == s.getName()) {
            s.assembly(tr);
            tr.createMapping();
        }
    }
}
// Param Train &tr is the (incomplete) train that gets assembled
void Simulator::assembleIncompleteTrain(Train &tr){

    //searching all stations to see where the train is

    for (auto &s : stations) {
        if (tr.getDepartureStation() == s.getName()) {
            s.assemblyIncomplete(tr);
            tr.createMapping();
        }
    }

}

// Param Train &tr is the train that is getting ready
void Simulator::gettingTrainReady(Train &tr) {
    tr.setStatus(TRAIN_LIFE_CYCLE[3]);
    tr.setLastAction(tr.getNextAction());
    tr.setNextAction(tr.getDepartureTime() );
}

// Param Train &tr is the train that gets running
void Simulator::gettingTrainRunning(Train &tr){
    Time arrival = calculateArrivalTime(tr);
    tr.setLastAction(tr.getNextAction());
    tr.setNextAction(arrival);
    tr.setArrivalTime(arrival);
    tr.setStatus(TRAIN_LIFE_CYCLE[4]);

    //calcuclate and set actual speed
    calculateAndSetActualSpeed(tr);
}

// Param Train &tr is the train that arrives
void Simulator::trainIsArriving(Train &tr) {
    tr.setLastAction(tr.getNextAction());
    tr.addToNextAction(ARRIVED);
    tr.setStatus(TRAIN_LIFE_CYCLE[5]);
}

// Param Train &tr is the train that finishes
void Simulator::trainIsFinishing(Train &tr){

    //searching all stations to see where the train should be picked apart
    for (auto &s : stations) {
        if (tr.getDestinationStation() == s.getName()) {

            tr.setLastAction(tr.getNextAction());
            s.deassemblyTrain(tr);
            tr.setStatus(TRAIN_LIFE_CYCLE[6]);
        }
    }
}

//prints the status of a train after each status update inside the simulation
//Param Train &tr is the train whos staus we print
void Simulator::printStatus(Train const &tr){
    std::cout << tr.getLastAction()<< " ";
    printTrain(tr);//this works if highlevel is to print vehicles

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[1]){
        std::cout <<"is now incomplete, next try at";
        std::cout <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[2]){
        std::cout <<"is now assembled, arriving at the platform at ";
        std::cout <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[3]){
        std::cout <<"now at the platform, departing at ";
        std::cout <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[4]){
        std::cout <<"has left the platform, traveling at speed ";
        // I think this is what we want
        std::cout <<tr.getActualSpeed()<< " ("<<tr.getMaxSpeed()<<")"<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[5]){
        std::cout <<"has arrived at the platform, disassembly at: ";
        std::cout <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[6]){
        std::cout <<"is now disassembled."<<std::endl;

    }
    std::cout <<std::endl;

}

//Param Train tr that is logged to logfile
void Simulator::logStatus(Train const &tr){
    outFile << tr.getLastAction()<< " ";


    logTrain(tr);//this works if highlevel is to print vehicles

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[1]){
        outFile <<"is now incomplete, next try at";
        outFile <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[2]){
        outFile <<"is now assembled, arriving at the platform at ";
        outFile <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[3]){
        outFile <<"now at the platform, departing at ";
        outFile <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[4]){
        outFile <<"has left the platform, traveling at speed ";
        outFile <<tr.getActualSpeed()<< " ("<<tr.getMaxSpeed()<<")"<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[5]){
        outFile <<"has arrived at the platform, disassembly at: ";
        outFile <<tr.getNextAction()<<std::endl;
    }

    if(tr.getStatus() ==TRAIN_LIFE_CYCLE[6]){
        outFile <<"is now disassembled."<<std::endl;

    }
    outFile <<std::endl;
}

void Simulator::sortTrainsByAction(){
    sort( theTrains.begin( ), theTrains.end( ), [ ]( const Train& t1, const Train& t2 )
    {
        if(t1.getNextAction() == t2.getNextAction()){
            return t1.getTrainNumber() < t2.getTrainNumber();
        }
        return t1.getNextAction() < t2.getNextAction();
    });
}

void Simulator::sortTrainsByTrainNumber(){
    sort( theTrains.begin( ), theTrains.end( ), [ ]( const Train& t1, const Train& t2 )
    {
        return t1.getTrainNumber() < t2.getTrainNumber();
    });
}

// Param city1 and city2 are matched against cities in distances
// Return the distance, 0 if not found
int Simulator::getDistance(std::string city1, std::string city2){
    for(const auto &d : distances){
        if( (d.city1 == city1 && d.city2 == city2) ||
            (d.city2 == city1 && d.city1 == city2) ){
            return d.dist;
        }
    }

    return 0;
}
//Param Train &tr is the train whos speed we calculate and sets
void Simulator::calculateAndSetActualSpeed(Train &tr){

    double distance = getDistance(tr.getDepartureStation(),tr.getDestinationStation());
    Time travelTime(tr.getArrivalTime() - tr.getDepartureTime());
    double time =  (travelTime.getHours() + travelTime.getMinutes()/60.0);
    double speed = distance / time;
    tr.setActualSpeed(speed);
}

bool Simulator::startMenu(){
    while(true) {

        std::cout << "Start menu" << std::endl;
        std::cout << "1. Change start time [" << startingTime << "]" <<std::endl;
        std::cout << "2. Change end time [" << endingTime << "]" <<std::endl;
        std::cout << "3. Start simulation" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout <<"Make a choice between 0 and 3"<<std::endl;
        int choice = getIntBetween(0,3);
        int time1,time2;

        switch (choice) {
            case 0:
                //end menu and end simulation
                return false;
            case 1:
                std::cout<<"Enter hours for when the simulation should start: "<<std::endl;
                time1 = getIntBetween(0,23);
                std::cout<<"Enter minutes for when the simulation should start: "<<std::endl;
                time2 = getIntBetween(0,59);
                startingTime = Time(time1,time2);
                std::cout <<"The simulation will now start at "<<
                          startingTime <<std::endl;

                break;
            case 2:
                std::cout<<"Enter hours for when the simulation should end: "<<std::endl;
                time1 = getIntBetween(0,23);
                std::cout<<"Enter minutes for when the simulation should end: "<<std::endl;
                time2 = getIntBetween(0,59);
                endingTime = Time(time1,time2);
                if(endingTime < startingTime){
                    std::cout <<"Simulation cannot end before it starts"<<std::endl;
                    endingTime = startingTime;
                }
                std::cout <<"The simulation will now end at "<< endingTime <<std::endl;
                break;
            case 3:
                //end menu and start simulation!
                return true;
            default:
                break;
        }
    }
}

void Simulator::simulationMenu(){

    while(true) {

        std::cout << "Simulation menu: current time: [" << timer <<"]"<< std::endl;
        std::cout << "1. Change interval " << interval << std::endl;
        std::cout << "2. Run next interval" << std::endl;
        std::cout << "3. Next event" << std::endl;
        std::cout << "4. Finish (Complete simulation)" << std::endl;
        std::cout << "5. Change log level " << logLevel << std::endl;
        std::cout << "6. Train menu" << std::endl;
        std::cout << "7. Station menu" << std::endl;
        std::cout << "8. Vehicle menu" << std::endl;
        std::cout << "0. Return" << std::endl; // return to where? start menu? and reset everything?

        std::cout << "Make a choice between 0 and 8" << std::endl;
        int choice = getIntBetween(0, 8);

        switch (choice) {
            case 0:
                redo = true;
                return;
            case 1:
                changeInterval();
                getInput();
                break;

            case 2:
                // running a interval is the standard thing to do
                return;
            case 3:
                doNextEvent();
                getInput();
                break;
            case 4:
                // by turning of the menu, the Simulation will run
                showMenu = false;
                return;
            case 5:
                changeLogLevel();
                getInput();
                break;
            case 6:
                trainMenu();
                getInput();
                break;
            case 7:
                stationMenu();
                getInput();
                break;
            case 8:
                vehicleMenu();
                getInput();
                break;
            default:
                break;
        }
    }
}

void Simulator::changeInterval(){
    int hours,minutes;

    std::cout<<"Enter hours for the interval:"<<std::endl;
    hours = getIntBetween(0,23);
    std::cout<<"Enter minutes for the interval: "<<std::endl;
    minutes = getIntBetween(0,59);
    interval = Time(hours,minutes);
    if(interval == Time(0,0)){
        std::cout <<"The interval cannot be  "<< interval <<std::endl;
        interval = Time(0,10);
    }

    std::cout <<"The interval is now "<< interval <<std::endl;

}

//add time until next event and execute that event
void Simulator::doNextEvent(){

    //update timer until we have an event
    sortTrainsByAction();
    //std::cout <<timer << " - "<< theTrains[0].getNextAction()<<std::endl;

    for(auto &tr : theTrains){
            if( tr.getStatus() != TRAIN_LIFE_CYCLE[6] ){
                timer = tr.getNextAction();
                trainLifeCycle(tr);
                break;
            }
        }

    /*
    while(timer < theTrains[0].getNextAction()){
        std::cout <<timer << " - "<< theTrains[0].getNextAction()<<std::endl;
        timer = timer + interval;

        for(auto &tr:theTrains){

        }
    }

    trainLifeCycle(theTrains[0]);

    // trainLifeCycle jumps one interval, so we take it back
    //reverseTime(interval);
    */
     sortTrainsByAction();

}

void Simulator::changeLogLevel(){

    if(logLevel == LOG_LOW){
        logLevel = LOG_HIGH;
    }
    else{
        logLevel = LOG_LOW;
    }

    std::cout <<"Log level is now changed to: " << logLevel <<std::endl;

}

void Simulator::trainMenu() {

    while (true) {
        std::cout << "Train menu: current time: [" << timer <<"]"<< std::endl;
        std::cout << "1. Search train by number " << std::endl;
        std::cout << "2. Search train by vehicle id" << std::endl;
        std::cout << "3. Change log level " << logLevel<< std::endl;
        std::cout << "0. Return " << std::endl;

        std::cout << "Enter a number between 0 and 4"<<std::endl;
        int choice = getIntBetween(0, 4);
        switch (choice) {
            case 0:
                return;
            case 1:
                searchTrainByNumber();
                getInput();
                break;
            case 2:
                searchTrainByVehicleID();
                getInput();
                break;
            case 3:
                changeLogLevel();
                getInput();
                break;
            default:
                break;
        }
    }
}

void Simulator::searchTrainByNumber(){
    long unsigned nrOfTrains = theTrains.size();
    int minNumber = 0;
    int maxNumber = 0;
    unsigned rowCounter = 0;
    sortTrainsByTrainNumber();
    for(auto const &tr: theTrains){

        std::cout << tr.getTrainNumber();
        maxNumber = std::max(maxNumber, tr.getTrainNumber());
        minNumber = std::min(minNumber, tr.getTrainNumber());
        if( (rowCounter%15 == 0 && rowCounter != 0) || rowCounter == (nrOfTrains -1) ){
            std::cout<<std::endl;
        }
        else{
            std::cout<< ", ";
        }
        rowCounter++;
    }
    std::cout <<"Pick a train number!"<<std::endl;
    int trainNr = getIntBetween(minNumber,maxNumber);
    for(auto const &tr: theTrains){
        if(trainNr == tr.getTrainNumber()){
            printTrain(tr);
        }
    }

    sortTrainsByAction();
}

void Simulator::searchTrainByVehicleID(){

    std::cout << "Enter a train id between "<<lowestVehicleNr <<
                 " and " <<highestVehicleNr <<": " << std::endl;
    int id = getIntBetween(lowestVehicleNr, highestVehicleNr); // can we get this not hardcoded? maybe when we read the file
    for(auto &tr : theTrains){
        if(tr.hasVehicle(id)){
            printTrain(tr);
        }
    }
}

//prints baseinfo, delay,speed and can print vehicles
void Simulator::printTrain(Train const &tr){
    printTrainBaseInfo(tr);
    std::cout<<std::endl;
    std::cout << "delay ("<< (tr.getArrivalTime() - tr.getOriginalArrivalTime())<<") ";
    std::cout << "speed = "<<tr.getActualSpeed()<<" km/h"<<std::endl;

    if(logLevel == LOG_HIGH){
        tr.printVehicleTypes();
    }
}

void Simulator::logTrain(Train const &tr){
    outFile <<"Train ["<<tr.getTrainNumber()<<"] ";
    outFile << "("<<tr.getStatus()<<") ";
    outFile <<"from "<<tr.getDepartureStation()<<" ";
    outFile << tr.getOriginalDepartureTime();
    outFile << "("<<tr.getDepartureTime()<<") ";
    outFile <<"to "<<tr.getDestinationStation()<<" ";
    outFile << tr.getOriginalArrivalTime();
    outFile << "("<<tr.getArrivalTime()<<") ";

    outFile <<std::endl;
    outFile << "delay ("<< (tr.getArrivalTime() - tr.getOriginalArrivalTime())<<") ";
    outFile << "speed = "<<tr.getActualSpeed()<<" km/h"<<std::endl;

}

void Simulator::printTrainBaseInfo(Train const &tr){
    std::cout <<"Train ["<<tr.getTrainNumber()<<"] ";
    std::cout << "("<<tr.getStatus()<<") ";
    std::cout <<"from "<<tr.getDepartureStation()<<" ";
    std::cout << tr.getOriginalDepartureTime();
    std::cout << "("<<tr.getDepartureTime()<<") ";
    std::cout <<"to "<<tr.getDestinationStation()<<" ";
    std::cout << tr.getOriginalArrivalTime();
    std::cout << "("<<tr.getArrivalTime()<<") ";
}


void Simulator::stationMenu() {
    while (true) {
        std::cout << "Station menu: current time: [" << timer <<"]"<< std::endl;
        std::cout << "1. Show station by name " << std::endl;
        std::cout << "2. Change log level " << logLevel<< std::endl;
        std::cout << "0. Return " << std::endl;
        std::cout <<"Make a choice between 0 and 2"<<std::endl;
        int choice = getIntBetween(0, 2);
        switch (choice) {
            case 0:
                return;
            case 1:
                searchStationByName();
                getInput();
                break;
            case 2:
                changeLogLevel();
                getInput();
                break;
            default:
                break;
        }
    }
}

void Simulator::searchStationByName(){

    unsigned rowCounter = 0;
    for(auto & s: stations){
        std::cout <<s.getName();
        if( (rowCounter%5 == 0 && rowCounter != 0) || rowCounter == (stations.size() -1) ){
            std::cout<<std::endl;
        }
        else{
            std::cout<< ", ";
        }
        rowCounter++;
    }
    std::cout <<"Pick a station!"<<std::endl;
    std::string stationName;
    getline(std::cin, stationName);
    for(auto &s: stations){
        if (stationName == s.getName()){
            s.print(logLevel);
        }
    }

}

void Simulator::vehicleMenu() {
    while (true) {
        std::cout << "Vehicle menu: current time: [" << timer <<"]"<< std::endl;
        std::cout << "1. Show vehicle by id " << std::endl;
        std::cout << "2. Change log level " << logLevel<< std::endl;
        std::cout << "0. Return " << std::endl;
        int choice = getIntBetween(0, 2);
        switch (choice) {
            case 0:
                return;
            case 1:
                searchVehicleByID();
                getInput();
                break;
            case 2:
                changeLogLevel();
                getInput();
                break;
            default:
                break;
        }
    }
}

// Searches in theTrain and all Stations after vehicle
void Simulator::searchVehicleByID(){
    std::cout <<"Enter vehicle ID"<<std::endl;
    int id = getIntBetween(0,9999);
    for(auto const &tr: theTrains){
        tr.findVehicle(id,logLevel);

    }

    for(auto const &s: stations){
        s.findVehicle(id,logLevel);
    }

}

void Simulator::statisticsMenu(){
    while (true) {
        std::cout << "Statistics menu: current time: [" << timer <<"]"<< std::endl;
        std::cout << "1. Change log level " << logLevel<<std::endl;
        std::cout << "2. Print statistics"<< std::endl;
        std::cout << "3. Train menu" << std::endl;
        std::cout << "4. Station menu" << std::endl;
        std::cout << "5. Vehicle menu" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout <<"Make a choice between 0 and 5"<<std::endl;
        int choice = getIntBetween(0, 5);
        switch (choice) {
            case 0:
                outFile.close();
                return;
            case 1:
                changeLogLevel();
                getInput();
                break;
            case 2:
                printStatistics();
                getInput();
                break;
            case 3:
                trainMenu();
                break;
            case 4:
                stationMenu();
                break;
            case 5:
                vehicleMenu();
                break;
            default:
                break;
        }
    }
}

// prints vehicles at start of simulation
// Total delay and end time for simulation
// Trains that never left the station
// Delayed (departure and Arrival) trains and their delay time
void Simulator::printStatistics(){

    std::cout<<"End time for simulation "<<timer<<std::endl;
    std::cout <<std::endl;

    nrOfVehiclesAtStartInStation();

    trainsThatNeverLeft();

    delayedTrains();

    std::cout <<"Total arrival delay time:  "<< totalDelay<<std::endl;
    std::cout <<std::endl;

    delayedDepartures();
    
}

void Simulator::nrOfVehiclesAtStartInStation(){
    std::cout <<"Number of vehicles at start of simulation:"<<std::endl;
    for(auto  const &s: stations){
        std::cout <<"\t"<< s.getName() <<" = "<<s.getTotalNrOfVehicles()<<std::endl;
    }

    std::cout <<std::endl;
}
void Simulator::trainsThatNeverLeft(){
    int neverLeftCounter =0;
    for(auto const &t: theTrains) {
        if(t.getStatus() == TRAIN_LIFE_CYCLE[1]){
            neverLeftCounter++;
        }
    }

    std::cout <<"Trains that never left the station ("<<neverLeftCounter<<"):" << std::endl;
    for(auto const &tr: theTrains){
        if(tr.getStatus() == TRAIN_LIFE_CYCLE[1]){
            printTrainBaseInfo(tr);
            std::cout <<std::endl;
            if(logLevel==LOG_HIGH){
                tr.printVehicleTypes();
            }
        }
    }

    std::cout <<std::endl;
}

void Simulator::delayedTrains(){
    int delayedCounter =0;
    for(auto const &tr: theTrains) {
        if(tr.getDelayed() == true){
            delayedCounter++;
        }
    }

    std::cout <<"Delayed trains at arrival ("<<delayedCounter<<"):" << std::endl;

    for(auto const &tr: theTrains){
        if(tr.getDelayed() == true){
            printTrainBaseInfo(tr);
            std::cout <<std::endl;
            std::cout <<"Delay: "<<tr.getArrivalTime()- tr.getOriginalArrivalTime()<<std::endl;
            if(logLevel==LOG_HIGH){

                tr.printVehicleTypes();
            }
        }

    }
}

void Simulator::delayedDepartures(){

    int delayedCounter =0;
    for(auto const &tr: theTrains) {
        if(Time(0,0) < tr.getDepartureTime() - tr.getOriginalDepartureTime() &&
        tr.getStatus() ==TRAIN_LIFE_CYCLE[6]){

            delayedCounter++;
        }
    }

    std::cout <<"Delayed trains at depature ("<<delayedCounter<<"):" << std::endl;

    Time departureDelay = Time(0,0);
    for(auto const &tr: theTrains){
        if(Time(0,0) < tr.getDepartureTime() - tr.getOriginalDepartureTime()
           && tr.getStatus() == TRAIN_LIFE_CYCLE[6]){
            printTrainBaseInfo(tr);
            std::cout <<std::endl;
            std::cout <<"Delay: "<<tr.getDepartureTime()- tr.getOriginalDepartureTime()<<std::endl;
            departureDelay += tr.getDepartureTime() - tr.getOriginalDepartureTime();
            if(logLevel==LOG_HIGH){
                tr.printVehicleTypes();
            }
        }

    }

    std::cout <<"Total depature delay "<<departureDelay <<std::endl;
}
