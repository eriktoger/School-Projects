//
// Created by erik on 2018-12-12.
//

#ifndef ERTG1700_SOLUTIONS_CONSTANTS_H
#define ERTG1700_SOLUTIONS_CONSTANTS_H
#include <vector>
#include <string>
using std::string;
using std::vector;

const  char DELIM = '|';

struct person {
    string firstName;
    string lastName;
    string signature;
    double height;
};

enum sortChoice {nameSort = 1, signSort = 2, heightSort = 3, randSort = 4};

const vector <string> MENUCHOICESVECTOR = {"Lägg till person", "Skriv ut personer", "Sök efter person","Ta bort person",
                                         "Sortera eller slumpa", "Spara listan till fil", "Läs in lista från fil",
                                         "Avsluta"};
#endif //ERTG1700_SOLUTIONS_CONSTANTS_H

