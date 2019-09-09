//
// Helper functions that are used in more than one class
//

#ifndef DT060G_ERTG1700_HELPFUNCTIONS_H
#define DT060G_ERTG1700_HELPFUNCTIONS_H
void printCoach(Coach const &c);
void printSleeping(Sleeping const &s);
void printOpen(OpenFreight const &o);
void printCoverd(CoverdFreight const &c);
void printElectrical(Electrical const &e);
void printDiesel(Diesel const &e);
void printHistory(std::vector <std::string> history);

void getInput();
int getIntBetween(int lower, int higher);
#endif //DT060G_ERTG1700_HELPFUNCTIONS_H
