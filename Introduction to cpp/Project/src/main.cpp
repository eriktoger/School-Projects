#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "../include/constants.h"
#include "../include/functionPrototypes.h"
#include "functionDefinitions.cpp"


using std::cout;
using std::endl;
using std::vector;
using std::string;


/*
 * This program lets the user add person into a list.
 * The list can be searched and sorted.
 * The program also prints the list
 * And can save and read from file with encryption.
 * */

int main() {
    cout << "Project!" << endl;
    vector <person> personVector;

    int choice = 0;

    while( choice != MENUCHOICESVECTOR.size() ) { // last one is always exit

        cout << endl;
        cout << "Din lista innehåller " << personVector.size() << " st personer"<<endl;
        choice = menu(MENUCHOICESVECTOR);

        switch (choice) {
            case 1:
                addPerson(personVector);
                break;
            case 2:
               printList(personVector);
                break;
            case 3:
                searchPerson(personVector);
                break;
            case 4:
                removePerson(personVector);
                break;
            case 5:
                sortChoice(personVector);
                break;
            case 6:
                saveToFile(personVector);
                break;
            case 7:
                readFromFile(personVector);
                break;
            case 8:
                cout << "Hej då!" << endl;
                break;
            default:
                cout << "Error" << endl;
        }
    }

    return 0;
}
