//
// Helper functions that are used in more than one class
//
#include "Coach.h"
#include "Sleeping.h"
#include "OpenFreight.h"
#include "CoverdFreight.h"
#include "Electrical.h"
#include "Diesel.h"

void printCoach(Coach const &c){
    std::cout <<"\t\t" <<"["<<c.getTypeName()<<"] ";
    std::cout <<"id: "<<c.getId()<<", ";
    std::cout <<c.getNumberOfChairs()<<" seats,";
    if(!c.getInternet()) {
        std::cout << " no";
    }
    std::cout <<" internet onboard."<<std::endl;
}

void printSleeping(Sleeping const &s){
    std::cout <<"\t\t" <<"["<<s.getTypeName()<<"] ";
    std::cout <<"id: "<<s.getId()<<", ";
    std::cout << s.getNumberOfBeds() <<" beads."<<std::endl;
}

void printOpen(OpenFreight const &o){
    std::cout <<"\t\t" <<"["<<o.getTypeName()<<"] ";
    std::cout <<"id: "<<o.getId()<<", ";
    std::cout <<"Area "<<o.getArea()<<" m² , ";
    std::cout <<"Capacity "<<o.getCapacity()<<" ton."<<std::endl;
}

void printCoverd(CoverdFreight const &c){
    std::cout <<"\t\t" <<"["<<c.getTypeName()<<"] ";
    std::cout <<"id: "<<c.getId()<<", ";
    std::cout <<"Cargo volume "<<c.getCapacity()<<" m³."<<std::endl;
}

void printElectrical(Electrical const &e){
    std::cout <<"\t\t" <<"["<<e.getTypeName()<<"] ";
    std::cout <<"id: "<<e.getId()<<", ";
    std::cout <<"max speed: " << e.getSpeed()<<" km/h, ";
    std::cout <<"power " <<e.getPowerKW()<< "kw."<<std::endl;
}

void printDiesel(Diesel const &e){
    std::cout <<"\t\t" <<"["<<e.getTypeName()<<"] ";
    std::cout <<"id: "<<e.getId()<<", ";
    std::cout <<"max speed: " << e.getSpeed()<<" km/h, ";
    std::cout <<"fuel consumption: " <<e.getFuelUsage()<< "l/h."<<std::endl;
}

void printHistory(std::vector <std::string> history) {

    std::cout<<"\t\t" <<"History (last entry is current location): "<<std::endl;
    int counter = 1;
    std::cout << "\t\t";
    for(auto const &h : history){
        std::cout  <<h;
        if(counter == 0 || counter %3 != 0){
            std::cout<<", ";
        }
        else{
            std::cout <<std::endl<< "\t\t";
        }
        counter++;
    }
    std::cout <<std::endl;
}

void getInput(){
    std::string line;
    std::cout <<"Press enter to continue"<<std::endl;
    getline(std::cin,line);
}

int getIntBetween(int lower, int higher){
    int choice;
    std::string line;
    bool isDigits;
    while (true) {

        isDigits = true;

        getline(std::cin, line);
        for (const auto &c : line) {
            if (!isdigit(c)) {
                isDigits = false;
                break;
            }
        }
        if (isDigits && !line.empty()) {
            choice = stoi(line);

            if(choice >= lower && choice <= higher){
                return choice;
            }
        }

    }
}