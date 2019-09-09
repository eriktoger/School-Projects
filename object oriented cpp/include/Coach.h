// Class: Coach
// A type of wagon
//

#ifndef DT060G_ERTG1700_COACH_H
#define DT060G_ERTG1700_COACH_H

#include "Vehicle.h"
#include "constants.h"


class Coach: public Vehicle {
private:
    int numberOfChairs;
    bool internet;
    std::string typeName = VEHICLE_NAMES[0];
public:
    // Constructor
    Coach(int idInput, int numberOfCharsInput, bool internetInput);

    //Getters
    int type() override  {return COACH;};
    int getNumberOfChairs()const {return numberOfChairs;};
    bool getInternet() const {return internet;};
    std::string getTypeName()const {return typeName;};
};


#endif //DT060G_ERTG1700_COACH_H
