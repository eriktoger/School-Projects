// Class: CoverdFreight
// A type of wagon
//

#ifndef DT060G_ERTG1700_COVERDFREIGHT_H
#define DT060G_ERTG1700_COVERDFREIGHT_H


#include "Vehicle.h"
#include "constants.h"


class CoverdFreight : public Vehicle {
private:
    std::string typeName = VEHICLE_NAMES[3];
    int capacity;
public:
    //Constructor
    CoverdFreight(int idInput, int capacityInput);

    //Getters
    int type() override {return COVERDFREIGHT; };
    int getCapacity()const{return capacity;};
    std::string getTypeName() const {return typeName;};
};


#endif //DT060G_ERTG1700_COVERDFREIGHT_H
