// Class: Diesel
// A type of wagon
//

#ifndef DT060G_ERTG1700_DIESEL_H
#define DT060G_ERTG1700_DIESEL_H

#include "Vehicle.h"
#include "constants.h"

class Diesel : public Vehicle {
private:
    int speed;
    int fuelUsage;
    std::string typeName = VEHICLE_NAMES[5];
public:
    //Constructor
    Diesel(int idInput, int speedInput, int fuelUsageInput);

    //Getters
    int type() override { return DIESEL;};
    int getSpeed() const {return speed;};
    int getFuelUsage() const {return fuelUsage;};
    std::string getTypeName()const {return typeName;};
};


#endif //DT060G_ERTG1700_DIESEL_H
