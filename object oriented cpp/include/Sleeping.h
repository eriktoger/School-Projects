// Class: Sleeping
// A type of wagon
//

#ifndef DT060G_ERTG1700_SLEEPING_H
#define DT060G_ERTG1700_SLEEPING_H

#include "Vehicle.h"
#include "constants.h"
class Sleeping: public Vehicle {
private:
    int numberOfBeds;
    std::string typeName = VEHICLE_NAMES[1];
public:
    Sleeping(int idInput, int numberOfBedsInput);
    int type() override {return SLEEPING;}; // not abstact
    int getNumberOfBeds() const{return numberOfBeds;};
    std::string getTypeName()const {return typeName;};
};


#endif //DT060G_ERTG1700_SLEEPING_H
