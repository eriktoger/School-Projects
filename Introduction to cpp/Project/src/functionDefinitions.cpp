//
// Created by erik on 2018-12-12.
//
#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random> // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
#include <fstream>
#include <sstream>
#include <cmath>
#include "../include/constants.h" // didnt need this before
#include "../include/functionPrototypes.h" // didnt need this before

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::to_string;
using std::setw;
using std::right;
using std::left;
using std::sort;
using std::fixed;
using std::setprecision;
using std::transform;

//------------------------------------------------------------------------------
// menu
//------------------------------------------------------------------------------
// Uppgift:  prints the menu and let the user make a choice
// Indata : vector <string> MENUCHOICESVECTOR
// Utdata : int choice
//------------------------------------------------------------------------------
int menu(vector<string> const &MENUCHOICESVECTOR) {

    cout << endl;
    cout << "Meny" << endl;
    cout << endl;

    /*
     * I didnt want one long column but instead two
     * but this was trickier than i thought.
     * åäö counts as 2 chars in .size() but 1 char on screen.
     * So I have to count the number of åäö in my string and deduct 1 for each.
     * I also added a extra space if the menu is bigger than 10, since this i likley to happen
     * if I expand my program just a little bit.
     * My code only works for two columns
     * */

    int counter = 1;
    int maxLength = 0;
    vector <int> strangeCharVector;
    int halfSize = std::round ( MENUCHOICESVECTOR.size()/2.0);

    // calulating the max printed lenght of the menu
    maxLength = calcMaxLengthAndSCVector(MENUCHOICESVECTOR,strangeCharVector);


    // printing the menu
    printMenu(MENUCHOICESVECTOR, strangeCharVector,maxLength);
    int vectorSize = MENUCHOICESVECTOR.size();
    
    int choice = 0;
    // Need a number between 1 and number if menu-items
    while (choice < 1 || choice > (vectorSize)) {

        cout << "Vad vill du göra? Skriv in ett nummer från listan ovanför!" << endl;
        cin >> choice;

        if (!cin.good()) { // only accepts correct input.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    return choice;
}
//------------------------------------------------------------------------------
// calcMaxLengthAndSCVector
//------------------------------------------------------------------------------
// Uppgift: inside menu to calculate the longest string in MENUCHOICESVECTOR and
//          to update strangheCharVector with number of åäö
// Indata : vector <string> const &MENUCHOICESVECTOR,vector <int> &strangeCharVector
// Utdata :  return maxLength;
//------------------------------------------------------------------------------

int calcMaxLengthAndSCVector(vector <string> const &MENUCHOICESVECTOR,vector <int> &strangeCharVector){
    int maxLength = 0;
    int halfSize = std::round ( MENUCHOICESVECTOR.size()/2.0);

    for(int i = 0 ; i < halfSize; i++){

        int chars = 0;
        int strangeChars = 0; // counting åäö
        for(char c : MENUCHOICESVECTOR[i]) {
            chars++;
            int charInt = c; // åäö is negative

            if(charInt > 127 || charInt < 0){
                strangeChars++;
            }
        }

        strangeCharVector.push_back(strangeChars); // saves them to deduct textLength;
        chars -= strangeChars/2 ;
        maxLength = std::max(maxLength,chars);
    }

    return maxLength;

}

//------------------------------------------------------------------------------
// printMenu
//------------------------------------------------------------------------------
// Uppgift: inside menu to actually print the menu
// Indata : vector <string> const &MENUCHOICESVECTOR, vector <int> const &strangeCharVector, int const maxLength
// Utdata : -
//------------------------------------------------------------------------------
void printMenu( vector <string> const &MENUCHOICESVECTOR, vector <int> const &strangeCharVector, int const maxLength){

    int vectorSize = MENUCHOICESVECTOR.size();
    int halfSize = std::round ( MENUCHOICESVECTOR.size()/2.0);
    int counter = 1;
    int const columns = 2;

    for (int i = 0; i < halfSize ; i++) {
        int textLength = 0;
        int strangeChars = 0;

        // finding the current printed length
        textLength = MENUCHOICESVECTOR[i].size();
        textLength -= strangeCharVector[ (counter-1)] / 2; // åäö counts as 2 chars but outputs 1.
        if(counter < 10 && vectorSize > 10){
            cout<< " "; // compensate if the vector has 10-99 items
        }

        // printing a row, containing two columns
        cout <<counter << ". " << MENUCHOICESVECTOR[i] << setw( ( maxLength - textLength ) + 5);

        if(i+halfSize < vectorSize){ // in case of odd length vector the last one dosnt exist
            cout <<counter+halfSize << ". " << MENUCHOICESVECTOR[i+halfSize] <<endl;
        }

        counter++;
    }

    if(vectorSize % columns == 1){
        cout << endl; // if the last row doesnt end with a endl, we add one
    }

    cout << endl;

}
//------------------------------------------------------------------------------
// createSignature
//------------------------------------------------------------------------------
// Uppgift: Creates the signature from first and last name (from person)
// Indata : vector <person> const &personVector, person person
// Utdata : string signature
//------------------------------------------------------------------------------
string createSignature(vector<person> const &personVector, const person &pers) {

    string firstName = pers.firstName;
    // lets bo einar have the three first as boe and not bo (ends with white space)
    remove_if(firstName.begin(), firstName.end(), isspace);

    string lastName = pers.lastName;
    remove_if(lastName.begin(), lastName.end(), isspace);

    // if name is less then 3 chars, fill up with x
    const int stringSize = 3;
    while (firstName.size() <= stringSize) {
        firstName += "x";
    }

    while (lastName.size() <= stringSize) {
        lastName += "x";
    }

    // get the first 3 chars from names
    firstName = firstName.substr(0, stringSize);
    lastName = lastName.substr(0, stringSize);
    string signature;// = "";

    // make them lower case
    for (char c: firstName) {
        signature += tolower(c);
    }

    for (char c: lastName) {
        signature += tolower(c);
    }

    // creates the standard counter suffix

    string signCounterString = "01";
    signature.append(signCounterString);

    // check if unique and maybe change 01 to 02

    // if not sorted by signature I have to go back to see if abcABC02 is used.
    // when sorted abcABC01 is followed by abcABC02 and so on.
    vector<person> newSortedPV = personVector;
    sort(newSortedPV.begin(), newSortedPV.end(), compareBySignature);

    bool unique = false;
    int signCounter = 1;
    while (!unique) {
        unique = true;
        for (person personSort : newSortedPV) {
            if (personSort.signature == signature) {
                signCounter++;
                signature = signature.substr(0, stringSize * 2); // removes the signCounterString

                // makes 1 to 01
                if (signCounter < 10) {
                    signCounterString = "";
                    signCounterString.append("0");
                    signCounterString.append(to_string(signCounter));
                } else {
                    signCounterString = to_string(signCounter);
                }

                signature += signCounterString;
                unique = false;
                break;
            }
        }
        if (signCounter >= 99) { // we only have 2 digits for unique names
            cout << "Error!" << endl;
            break;
        }
    }

    return signature;
}

//------------------------------------------------------------------------------
// addPerson
//------------------------------------------------------------------------------
// Uppgift: lets the user add a new person to the list
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------
void addPerson(vector<person> &personVector) {

    cout << "Add person" << endl;
    person newPers;

    string firstName; //="";

    cin.ignore(INT_MAX, '\n');// cin.ignore(); // usally needed when we go från cin to getline
    while(firstName.empty()){
        cout << "First name:" << endl;
        getline(cin, firstName);
        firstName = removeSpace(firstName);
    }

    newPers.firstName = firstName;

    string lastName;// = "";
    while(lastName.empty()){
        cout << "Last name:" << endl;
        getline(cin, lastName);
        lastName = removeSpace(lastName);
    }

    newPers.lastName = lastName;

    newPers.signature = createSignature(personVector, newPers);

    double height = 0;
    bool heightOK = false;
    //cin.ignore(INT_MAX, '\n');
    while (!heightOK) {
        cout << "Height [m]: " << endl;
        cin >> height;
        cin.ignore(INT_MAX, '\n');
        if (!cin.good()) { // only accpts correct input.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } else if (height > 0 ){ // only positive heights are accepted
            heightOK = true;
        }
    }

    newPers.height = std::round( height * 100 ) / 100; // round to 2 decimals

    // is this correct? Do over or accept
    cout << "Is the data correct?" << endl
         << "First Name: " << newPers.firstName << endl
         << "Last Name: " << newPers.lastName << endl
         << "Signature: " << newPers.signature << endl
         << "Height: " << newPers.height << endl;

    // check if person is unique

    // have to convert to_lower before check.
    string firstNameA = newPers.firstName;
    string lastNameA = newPers.lastName;
    transform(firstNameA.begin(), firstNameA.end(), firstNameA.begin(), ::tolower);
    transform(lastNameA.begin(), lastNameA.end(), lastNameA.begin(), ::tolower);

    double heightA = newPers.height ;

    string userInput;
    bool isUnique = true;
    for (person pers : personVector) {
        // have to convert to_lower before check.
        string firstNameB = pers.firstName;
        string lastNameB = pers.lastName;
        transform(firstNameB.begin(), firstNameB.end(), firstNameB.begin(), ::tolower);
        transform(lastNameB.begin(), lastNameB.end(), lastNameB.begin(), ::tolower);

        double heightB = pers.height ;

        if (firstNameA == firstNameB && lastNameA == lastNameB
            && heightA == heightB) {

            isUnique = false;
            cout << "The person is not unique" << endl;
            cout << "Do you want to add the person anyway?"<<endl;

            while (userInput != "yes" && userInput != "no" && userInput != "change"){
                cout << "Enter yes to add, no to not add and change to reenter the information"<<endl;
                cin >> userInput;
                // Im not happy to use cin here. But otherwise the code gets funky.
                // this because cin is used before addperson is called from the meny
                // I think the right thing should be to use getline to read the number from
                // the user in menu
            }

            if(userInput == "change"){
                addPerson(personVector);
            }
            if(userInput == "yes"){
                personVector.push_back(newPers);
                cout << "Person added!" << endl;
            }
            if(userInput == "no"){
                cout << "Person was not added" << endl;
            }
            break;
        }
    }

    // since unique persons are asked already to be added
    // it felt unnecessary to ask again
    if( isUnique){
        cout << "Enter ok or OK to add person" << endl;
        getline(cin,userInput);
        if( userInput == "ok" || userInput == "OK"){
            personVector.push_back(newPers);
            cout << "Person added!" << endl;
        }
        else {
            cout << "Person was not added" << endl;
        }
    }

}

//------------------------------------------------------------------------------
// printList
//------------------------------------------------------------------------------
// Uppgift: prints the list of persons
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------
void printList(vector<person> const &personVector) {

    int counter = 1;
    cout << fixed << setprecision(2);
    string cont = "";
    cin.ignore(INT_MAX, '\n');
    //cin.clear();
    //cin.sync();
    int maxLength = 0;
    int stringLength;

    // find the longest name
    // otherwise will long names make the columns off sync.
    for (person pers : personVector){
        stringLength =  (pers.firstName).size() + (pers.lastName).size() ;
        maxLength = std::max ( maxLength,stringLength );
    }

    // 1,10,100 need different spaces when we print.
    int count = personVector.size();
    count = ( (int) log10(count) ) + 4;

    cout << left << setw(count) << "Nr ";
    cout << left << setw(count + 5) << "Sign ";
    cout << left << setw(count + maxLength + 9) << "Name";
    cout << right << setw(count + 6) << "Height [m]" << endl;

    for (person pers : personVector) {
        string number; // = "";
        number += to_string(counter);
        number += ".";

        // https://www.youtube.com/watch?v=6MsGZw_2hjs
        // the link was inspiration for my code
        cout << left << setw(count) << number;
        cout << left << setw(count + 5) << pers.signature;
        cout << left << setw(count + maxLength + 7) << pers.firstName + " " + pers.lastName;
        cout << right <<setw(count + 6) << pers.height << endl;

        if (counter % 20 == 0) {
            // sometimes you have to press enter twice, dont know why =(
            cout << "Press Enter to continue" << endl;
            getline(cin, cont);

            cout << left << setw(count) << "Nr ";
            cout << left << setw(count + 5) << "Sign ";
            cout << left << setw(count + maxLength + 9) << "Name";
            cout << right << setw(count + 6) << "Height [m]" << endl;
        }

        counter++;

    }
}

//------------------------------------------------------------------------------
// searchPerson
//------------------------------------------------------------------------------
// Uppgift: find if signature is in list.
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------
void searchPerson(vector<person> const &personVector) {

    string signature;
    cout << "Search for person" << endl;
    cout << "Please enter signature: " << endl;
    //cin.clear();
    //cin.sync();
    cin.ignore(INT_MAX, '\n'); //cin.ignore(); // need this otherwise wont getline wait for input
    getline(cin, signature);

    bool found = false;
    for (person pers : personVector) {
        if (pers.signature == signature) {
            printPerson(pers, signature);
            found = true;
            break;
        }
    }
    if (!found) {
        cout << signature << " was not found" << endl;
    }

}

//------------------------------------------------------------------------------
// printPerson
//------------------------------------------------------------------------------
// Uppgift: prints the a single persons
// Indata : const person &person, const string &signature
// Utdata : -
//------------------------------------------------------------------------------
void printPerson(const person &pers, const string &signature) {
    cout << fixed << setprecision(2);
    cout << signature << " was found!" << endl;

    // get length of name, otherwise will long names make the columns off sync.
    const int nameLength = pers.firstName.size() + pers.lastName.size();

    // i got this from:     https://www.youtube.com/watch?v=6MsGZw_2hjs
    cout << left << setw(9) << "Sign ";
    cout << left << setw(nameLength + 11) << "Name";
    cout << right << setw(10) << "Height [m]" << endl;

    cout << left << setw(9) << signature;
    cout << left << setw(nameLength + 9) << pers.firstName + " " + pers.lastName;
    cout << right << setw(10) << pers.height << endl;
}

//------------------------------------------------------------------------------
// removePerson
//------------------------------------------------------------------------------
// Uppgift: remove person if signature is in list.
// Indata : vector <person> const &personVector, string signature
// Utdata : -
//------------------------------------------------------------------------------
void removePerson(vector<person> &personVector) {

    string signature;
    cout << "Remove person" << endl;
    cout << "Please enter signature: " << endl;
    //cin.clear();
    //cin.sync();
    cin.ignore(INT_MAX, '\n'); // cin.ignore(); // need this otherwise wont getline wait for input
    getline(cin, signature);

    bool found = false;
    // removes all personons  with this signature
    for (person pers : personVector) {
        if (pers.signature == signature) {

            // https://stackoverflow.com/questions/32062126/how-to-remove-a-struct-element-from-a-vector
            personVector.erase(
                    std::remove_if(personVector.begin(), personVector.end(), [&](person const &pers) {
                        return pers.signature == signature;
                    }),
                    personVector.end());
            cout << signature << " was removed" << endl;

            found = true;
            break;
        }

    }
    if (!found) {
        cout << signature << " was not found and therefore not removed" << endl;
    }

}
//------------------------------------------------------------------------------
// sortPersonList
//------------------------------------------------------------------------------
// Uppgift: sort the list
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------

void sortPersonList(vector<person> &personVector, int choice) {


    auto rng = std::default_random_engine{}; // I this ok?
    // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

    switch (choice) {
        case nameSort:
            cout << "Sorting by name" << endl;
            sort(personVector.begin(), personVector.end(), compareByName);
            cout << "Sorted by name" << endl;
            break;
        case signSort:
            cout << "Sorting by signature" << endl;
            sort(personVector.begin(), personVector.end(), compareBySignature);
            cout << "Sorted by signature" << endl;
            break;
        case heightSort:
            cout << "Sorting by height (highest first)" << endl;
            sort(personVector.begin(), personVector.end(), compareByHeight);
            cout << "Sorted by height (highest first)" << endl;
            break;
        case randSort:
            cout << "RANDOMIZE!" << endl;
            std::shuffle(personVector.begin(), personVector.end(), rng);
            cout << "Randomized" << endl;
            break;
        default:
            cout << "Error" << endl;
    }
}

//------------------------------------------------------------------------------
// sortChoice
//------------------------------------------------------------------------------
// Uppgift: To make a choice and then call sortPersonList
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------

void sortChoice(vector<person> &personVector) {

    cout << "How do you want to sort your vector?" << endl;
    cout << "1. Lastname, 2. Signature, 3. Height or 4. Randomize? " << endl;

    int choice = 0;

    while (choice < 1 || choice > 5) {
        cout << "Please enter corrsponding number" << endl;
        cin >> choice;
        cin.ignore(INT_MAX, '\n');

        if (!cin.good()) { // only accpts correct input.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            choice = 0;
        }

    }

    sortPersonList(personVector, choice);

}

//------------------------------------------------------------------------------
// saveToFile
//------------------------------------------------------------------------------
// Uppgift: saves list to file
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------

void saveToFile(vector<person> const &personVector) {
    cout << "Save to file" << endl;
    cout << "Name the file you want to save to " << endl;
    string fileName;
    cin >> fileName;
    std::ofstream outFile(fileName);

    int rot = -1;
    // checks if input is correct.
    while (rot < 0 || rot > (255)) { // char is bounded by 0-255

        cout << "What rot do you want to use (enter 0 for no encrypton) ?" << endl;
        cin >> rot;

        if (!cin.good()) { // only accpts correct input.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            rot = -1;
        }
    }

    char newDelim = (DELIM + rot);

    for (person person : personVector) {

        outFile << encrypting(person.firstName, rot) << newDelim;
        outFile << encrypting(person.lastName, rot) << newDelim;
        outFile << encrypting(person.signature, rot) << newDelim;

        // otherwise is 1.7 written as 1.700000
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << person.height;
        string height = ss.str();
        outFile << encrypting(height, rot) << endl;
    }

    outFile.close();
    cout << "Saved to file" << endl;
}
//------------------------------------------------------------------------------
// readFromFile
//------------------------------------------------------------------------------
// Uppgift: read list from file
// Indata : vector <person> const &personVector
// Utdata : -
//------------------------------------------------------------------------------

void readFromFile(vector<person> &personVector) {

    cout << "Read from file" << endl;
    cout << "Name the file you want to read" << endl;
    string fileName;
    cin >> fileName;
    std::ifstream inFile(fileName);

    bool fileExist = true;
    int rot = -1;
    if (inFile.good()) {
        personVector.clear(); // clears the old list
        // checks if input is correct.
        while (rot < 0 || rot > (255)) { // char is bounded by 0-255

            cout << "What rot do you want to use (enter 0 for no decrypton) ?" << endl;
            cin >> rot;

            if (!cin.good()) { // only accpts correct input.
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                rot = -1;
            }
        }

    } else {
        cout << "File does not exist" << endl;
        fileExist = false;
    }

    char newDelim = (DELIM + rot);


    string line;
    int counter = 0;

    //double height;

    // every line should have 3 delimiters.
    // firstName is chars up to first delimiter.
    // lastName is chars between first and second.
    // signature between second and third.
    // and height is from third to end.
    // names cant be empty ( spaces are removed)
    // heights cant be negative
    // and then is the person pushed into the list.

    while (getline(inFile, line) && fileExist) {
        counter = 0;
        person pers;
        string word = "";
        for (char c : line) {
            if (c == newDelim) {
                switch (counter) {
                    case 0:
                        pers.firstName = removeSpace ( decrypting(word, rot) );
                        word = "";
                        break;
                    case 1:
                        pers.lastName = removeSpace( decrypting(word, rot) );
                        word = "";
                        break;
                    case 2:
                        pers.signature = removeSpace( decrypting(word, rot) );
                        word = "";
                        break;
                    default:
                        cout << "Error: to many delimiters in a line" << endl;
                }
                counter++;
            } // end if c == delimiter
            else {
                word += c;
            }
        } // end for char c

        try {
            pers.height = std::stod(decrypting(word, rot));
            pers.height = std::round(pers.height * 100 ) / 100; // round to 2 decimals
        }
        catch (std::invalid_argument &err) {
            pers.height = 0;
            cout << "there was an error with: " << err.what() << endl;
        }

        if (counter != 3) {

            cout << "Error: not three delimiters in a line, but :" << counter << endl;

        } else if( (pers.firstName).empty() || (pers.lastName).empty() || (pers.signature).empty() ) {

            cout << "Error: name or signature is empty:" << endl;

            } else if( pers.height < 0 ){

            cout <<"Error: height can not be negative"<<endl;

                } else{

                personVector.push_back(pers); // input is correct

                }
    } // end while

    if (fileExist) {
        cout << "File was read" << endl;
    }

}

//------------------------------------------------------------------------------
// compareByName
//------------------------------------------------------------------------------
// Uppgift: sort by last name and first name if last names are equal
// Indata : const person &a,const person &b
// Utdata : true or false
//------------------------------------------------------------------------------

// https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
bool compareByName(const person &a, const person &b) {

    string firstNameA = a.firstName;
    string lastNameA = a.lastName;

    string firstNameB = b.firstName;
    string lastNameB = b.lastName;

    // https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
    transform(firstNameA.begin(), firstNameA.end(), firstNameA.begin(), ::tolower);
    transform(firstNameB.begin(), firstNameB.end(), firstNameB.begin(), ::tolower);
    transform(lastNameA.begin(), lastNameA.end(), lastNameA.begin(), ::tolower);
    transform(lastNameB.begin(), lastNameB.end(), lastNameB.begin(), ::tolower);

    if (lastNameA == lastNameB) {
        return firstNameA < firstNameB;
    }

    return lastNameA < lastNameB;

}

//------------------------------------------------------------------------------
// compareBySignature
//------------------------------------------------------------------------------
// Uppgift: sort by signature
// Indata : const person &a,const person &b
// Utdata : true or false
//------------------------------------------------------------------------------
bool compareBySignature(const person &a, const person &b) {

    return a.signature < b.signature;

}

//------------------------------------------------------------------------------
// compareByHeight
//------------------------------------------------------------------------------
// Uppgift: sort by Height, but reversed. Highest first
// Indata : const person &a,const person &b
// Utdata : true or false
//------------------------------------------------------------------------------
bool compareByHeight(const person &a, const person &b) {

    return !(a.height < b.height);
}

//------------------------------------------------------------------------------
// encrypting
//------------------------------------------------------------------------------
// Uppgift: encrypt with rot
// Indata : string text, int rot
// Utdata : string encryptedText
//------------------------------------------------------------------------------
string encrypting(string const &text, int rot) {

    string encryptedText = "";

    for (char c : text) {
        encryptedText += (c + rot);
    }


    return encryptedText;
}

//------------------------------------------------------------------------------
// decrypting
//------------------------------------------------------------------------------
// Uppgift: decrypt with rot
// Indata : string text, int rot
// Utdata : string decryptedText
//------------------------------------------------------------------------------
string decrypting(string const &text, int rot) {

    string decryptedText = "";

    for (char c : text) {
        decryptedText += (c - rot);
    }

    return decryptedText;
}
//------------------------------------------------------------------------------
// removeSpace
//------------------------------------------------------------------------------
// Uppgift: removing leading and traling spaces
// Indata : string text
// Utdata : string text (with out spaces)
//------------------------------------------------------------------------------
string removeSpace(string text){

    int posFirst = 0; // first non-space

    for(int i = 0; i < text.size(); i++){
        posFirst = i;
        if( ! std::isspace(text[i]) ){
            break;
        }
    }

    text = text.substr(posFirst); // if only spaces, no spaces are removed

    int posLast = text.size()-1;  //last non-space

    for(int i = (text.size() - 1) ; i >= 0; i--){
        posLast = i;
        if( !std::isspace(text[i]) ){
            break;
        }
    }

    posLast++;// we want numner of chars, not the index of the last char

    text = text.substr(0,posLast);

    if(text == " "){ // if we have only spaces
        return "";
    }

    return text;
}