#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "HashTable.h"

using namespace std;

void printmenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Insert movie" << endl;
    cout << "2. Delete movie" << endl;
    cout << "3. Find movie" << endl;
    cout << "4. Print table contents" << endl;
    cout << "5. Quit" << endl;
}

int main()
{
    HashTable table;

    int input = -1;

    string title;
    string stryear;
    int intyear;

    while(input != 5){

        printmenu();
        cin >> input;
        cin.ignore();

        if(input == 1){
            cout << "Enter title:" << endl;
            getline(cin, title);
            cout << "Enter year:" << endl;
            getline(cin, stryear);
            intyear = atoi(stryear.c_str());
            table.insertMovie(title, intyear);
        }

        if(input == 2){
            cout << "Enter title:" << endl;
            getline(cin, title);
            table.deleteMovie(title);
        }

        if(input == 3){
            cout << "Enter title:" << endl;
            getline(cin, title);
            table.findMovie(title);
        }

        if(input == 4){
            table.printInventory();
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
