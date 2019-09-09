// Class: OpenFreight
// A type of wagon
//

#ifndef DT060G_ERTG1700_OPENFREIGHT_H
#define DT060G_ERTG1700_OPENFREIGHT_H


#include "Vehicle.h"
#include "constants.h"


class OpenFreight: public Vehicle {
private:
    int capacity;
    int area;
    std::string typeName = VEHICLE_NAMES[2];
public:

    //Constructor
    OpenFreight(int idInput, int capacityInput, int areaInput);

    //Getters
    int type() override {return OPENFREIGHT;}; // not abstact
    int getCapacity()const {return capacity;};
    int getArea()const {return area;};
    std::string getTypeName()const {return typeName;};
};


#endif //DT060G_ERTG1700_FREIGHT_H
