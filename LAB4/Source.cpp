#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

class Creature {
private:
    // member variables
    int strength;
    int health;
    string id;

public:
    // accessor functions
    int getStrength()const;
    int getHealth()const;
    string getID()const;
    string to_String()const;

    // mutator function
    void setCreature(int strength, int health, string ID);
};

int Creature::getStrength()const {
    return strength;
}

int Creature::getHealth()const {
    return health;
}

string Creature::getID()const {
    return id;
}

string Creature::to_String()const {       //  returns the creature's details
    stringstream ss;
    ss << setw(10) << left << id
        << setw(10) << right << health
        << setw(22) << right << strength << endl;
    return ss.str();
};

void Creature::setCreature(int stren, int heal, string ID) {
    strength = stren;
    health = heal;
    id = ID;
}

// function prototypes
int getData(Creature[]);
void print(Creature[]);
void SearchMenuOption(Creature[]);
string search(Creature[], string, bool&, int&);
string uppercase(string);
void SortMenuOption(Creature[]);
void sortCreatures(Creature[], int, int);

// constant variables
const int SIZE = 8;
const int MAX = 100;
const int MIN = 10;

enum Menu {
    PRINT = 1, SEARCH, SORT, QUIT
};

enum SortMenu {
    ID = 1, STRENGTH, HEALTH, BACK_TO_MAIN
};


int main() {
    Creature creatureArr[SIZE];
    int choice, check;

    check = getData(creatureArr);    // returns -1 if file is empty
    if (check == -1)
        cout << "Please update file and re-run program.\n";
    else {
        do {
            cout << endl << "Select one of the following options:\n"
                "[" << PRINT << "] Print creature info\n"
                "[" << SEARCH << "] Search by creature ID\n"
                "[" << SORT << "] Sort\n"
                "[" << QUIT << "] Quit\n";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');   // clear buffer

            switch (choice) {
            case PRINT:
                print(creatureArr);
                break;

            case SEARCH:
                SearchMenuOption(creatureArr);
                break;

            case SORT:
                SortMenuOption(creatureArr);
                break;

            case QUIT:
                cout << endl << "Goodbye...";
                break;

            default:
                cout << endl << "Invalid Input!\n";    // catch invalid input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        } while (choice != QUIT);
    }
    return 0;
}


//  update creature's details
int getData(Creature obj[]) {
    int check = 0;
    string id;
    ifstream infile("Text.txt");

    if (infile.fail())          // checks for errors when opening file
        cout << "Error opening file!";
    else {
        check = infile.peek();
        if (check == EOF)         // checks if file is empty
            cout << endl << "File is empty!\n";
        else {
            srand(time(0));
            int i = 0;
            while (infile >> id) {    // read file
              // set a random number between 10 and 100 for the strength and health
                obj[i].setCreature((rand() % (MAX - MIN)) + MIN, (rand() % (MAX - MIN)) + MIN, id);
                i++;
            }
        }
    }
    infile.close();    // close the file
    return check;
}


//  print creature's details
void print(Creature obj[]) {
    cout << endl << " ID" << ""
        << setw(19) << right << "Health" << ""
        << setw(23) << right << "Strength" << endl
        << setfill('-') << setw(47) << "" << setfill(' ') << endl;

    int i = 0;
    while (i < SIZE) {
        cout << obj[i].to_String();
        i++;
    }
}


void SearchMenuOption(Creature obj[]) {
    bool check = false;
    int count = 0;
    string str, results, match;

    cout << endl << "Enter creature ID: ";
    getline(cin, str);                        // get user input and convert to uppercase
    str = uppercase(str);

    results = search(obj, str, check, count);    // call to search function
    match = (count > 1) ? " matches were" : " match was";
    // print search results 
    if (check) {
        cout << endl << count << match << " found! \n"
            << endl << " ID" << ""
            << setw(19) << right << "Health" << ""
            << setw(23) << right << "Strength" << endl
            << setfill('-') << setw(47) << "" << setfill(' ') << endl
            << results;
    }
    else
        cout << endl << "No match found.\n";
}


string search(Creature obj[], string  str1, bool& check, int& count) {
    string str2, results;
    size_t found;

    int i = 0;
    while (i < SIZE) {
        str2 = uppercase(obj[i].getID());    // convert creature ID to uppercase
        found = str2.find(str1);
        if (found != string::npos) {
            check = true;
            results += obj[i].to_String();    // append creature details to string
            count++;
        }
        i++;
    }
    return results;        // return string
}


// converts any string argument to uppercase
string uppercase(string word) {
    for (int i = 0; i < word.length(); i++)
        word[i] = toupper(word[i]);

    return word;
}


void SortMenuOption(Creature obj[]) {
    int choice;
    do {
        cout << endl << "Sort by:\n" <<
            "[" << ID << "] ID\n" <<
            "[" << STRENGTH << "] Strength\n"
            "[" << HEALTH << "] Health\n"
            "[" << BACK_TO_MAIN << "] Main Menu\n";
        cin >> choice;

        switch (choice) {
        case ID:
        case STRENGTH:
        case HEALTH:
            sortCreatures(obj, SIZE, choice);    // call to sort function
            print(obj);                          // print sorted creatures
            break;

        case BACK_TO_MAIN:                     // option to return to main menu
            break;

        default:
            cout << endl << "Invalid Input!\n";  // catch invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    } while (choice != BACK_TO_MAIN);
}


// ascending bubble sort
void sortCreatures(Creature obj[], int numOfCreatures, int sortOption) {
    Creature temp;
    bool swap = false;

    for (int j = 0; j < numOfCreatures; j++) {
        for (int i = 0; i < numOfCreatures - j - 1; i++) {
            switch (sortOption) {
            case ID:
                swap = obj[i].getID() > obj[i + 1].getID();  // compare IDs
                break;

            case STRENGTH:
                swap = obj[i].getStrength() > obj[i + 1].getStrength(); // compare strengths
                break;

            case HEALTH:
                swap = obj[i].getHealth() > obj[i + 1].getHealth(); // compare healths
                break;
            }
            // swap creatures
            if (swap) {
                temp = obj[i];
                obj[i] = obj[i + 1];
                obj[i + 1] = temp;
            }
        }
    }
}


