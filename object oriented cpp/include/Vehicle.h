// Class: Vehicle
// The abstract base class for all other wagons.
//

#ifndef DT060G_ERTG1700_VEHICLE_H
#define DT060G_ERTG1700_VEHICLE_H

#include <string>
#include <vector>

class Vehicle {
public:
    int id;
    std::vector <std::string> history;
    virtual int type() = 0;
    virtual ~Vehicle()= default;
    virtual int getId() const {return id;};
    void addToHistory(std::string position){history.push_back(position);};
    std::vector <std::string> getHistory(){return history;};

private:

};


#endif //DT060G_ERTG1700_VEHICLE_H
