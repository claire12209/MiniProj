#include "header.h"

//main function

int main() {
    bool end = true;


    //create base dict with base commands
    populate_function_map();

    //select static typing
    cout << "Dynamic(1) or Static(2)? ";


    //get input string 
    int myint = 0;
    string s;
    getline(cin, s, '\n');

    myint = stoi(s);

    //error checking
    while (myint != 1 && myint != 2) {
        cout << "Error, input a valid typing" << endl;
        cout << "Dynamic(1) or Static(2)? " << endl;
        getline(cin, s, '\n');
        myint = stoi(s);

    }
    //set whether static or dynamic
    if (myint == 1) {
        staticvar = false;
    }
    else {
        staticvar = true;
    }

    //start loop until quit is chosen
    while (end) {
        string x = getting_line();
        if (x == "quit") {
            end = false;
        }
        else {
            parsing(x);
        }


    }

    return 0;
}
