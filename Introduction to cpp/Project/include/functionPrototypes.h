//
// Created by erik on 2018-12-12.
//

#ifndef ERTG1700_SOLUTIONS_FUNCTIONPROTOTYPES_H
#define ERTG1700_SOLUTIONS_FUNCTIONPROTOTYPES_H
#include "constants.h" // didnt need this before
#include <string> // didnt need this before
using std::string;
using std::vector;

int menu( vector <string> const &);
string createSignature(vector<person> const &personVector,const person &);
void printPerson(const person &,const string &);
int calcMaxLengthAndSCVector(vector <string> const &MENUCHOICESVECTOR,vector <int> &strangeCharVector);
void printMenu( vector <string> const &MENUCHOICESVECTOR, vector <int> const &strangeCharVector, int const);

// the menu alternetivs
void addPerson(vector <person> &);
void printList(vector <person> const &);
void searchPerson(vector <person> const &);
void removePerson(vector <person> &);
void sortChoice(vector<person> &);
void sortPersonList(vector <person> &, int);
void saveToFile(vector <person> const &);
void readFromFile(vector <person> &);

// comparing the list for sorting
bool compareByName(const person &a,const person &b);
bool compareBySignature(const person &a,const person &b);
bool compareByHeight(const person &a,const person &b);

// crypt and decyrpting the file.
string encrypting(string const &text, int rot);
string decrypting(string const &text, int rot);

string removeSpace(string text);

#endif //ERTG1700_SOLUTIONS_FUNCTIONPROTOTYPES_H
