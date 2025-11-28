#include "header.h"

//main function

int main() {
    bool end = true;


    //create base dict with base commands
    populate_function_map();

    //select static typing
  

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
