// Class: Electrical
// A type of wagon
//

#ifndef DT060G_ERTG1700_ELECTRICAL_H
#define DT060G_ERTG1700_ELECTRICAL_H


#include "Vehicle.h"
#include "constants.h"


class Electrical : public Vehicle {
private:
    int speed;
    int powerKW;
    std::string typeName = VEHICLE_NAMES[4];
public:

    //Constructor
    Electrical(int idInput, int speedInput, int powerKWInput);

    //Getters
    int type() override {return ELECTRICAL;};
    int getSpeed()const{return speed;};
    int getPowerKW()const{return powerKW;};
    std::string getTypeName()const {return typeName;};
};


#endif //DT060G_ERTG1700_ELECTRICAL_H
