#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <algorithm>

/*
Name: CLAIRE MONSON
class: CPTS 355
Description: A postscript interpreter that functions with stacks.

*/





using namespace std;

//The main stack to be operated on
stack <string> globalstack;

//the original function map with base commands
std::map<std::string, string> functionMap;

//a new dict to hold new dict
std::map<std::string, string> dictmap;


//stack of dicts (vector for iteration purposes)
vector<std::map<std::string, string>> dictStack;

//Is it static and current dict stack location
bool staticvar = false;
int currentDictStack = 0;


//function definition
void parsing(string x);
vector <string> splittingString(const string& s, const string& delim);
string string_check(int& j, vector <string>& s);
string procedure_check(int& j, vector <string>& s);
string array_check(int& j, vector <string>& s);
string getting_line(void) ;
void populate_function_map(void);
void call_command_on_stack(string currentCommand);
void nonemptyCommand(string currentCommand, vector <string>& s, int& j);
void exch();void copy();void dup();void add();void sub();void mul();void div();void mod();void idiv();void abs();void neg();
void ceiling();void floor();void sqrt();void dict();void length();void maxlength();void begin();void end();void def();void get();
void getinterval();void putinterval();void eq();void ne();void ge();void gt();void le();void lt();void andOp();void notOp();
void orOp();void iff();void iffelse();void forF();void repeat();void print();void equals();void equalsequals();void round();



/*
    Splits string into pieces based on " " delimiter as required by postscript
*/

vector <string> splittingString(const string& s, const string& delim) {
    vector <string> substringVector;

    size_t begin = 0; //start at beginning of string

    size_t end = s.find(delim); //find first instance of delimiter

    while (end != string::npos) { //while not at end of string

        substringVector.push_back(s.substr(begin, end - begin)); // add substring to vector for iteration
        begin = end + delim.length(); //get next begin and end
        end = s.find(delim, begin);

    }
    substringVector.push_back(s.substr(begin)); //push last string to vector
    return substringVector; //use vector for command calling
}


/*
START OF COMMANDS FUNCTIONS 
*/


/*
adds two numbers popped from stack and adds to stack
*/
void add(void) {
    globalstack.pop(); //remove "and" string 
    double a, b;
    try { //checks if numbers or not
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();

        double results = a + b;

        globalstack.push(to_string(results)); //push results to string
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into add" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}


/*
subtracts two numbers popped from stack and adds to stack
*/
void sub(void) {
    globalstack.pop();
    double a, b;
    try {
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();

        double results = b - a;

        globalstack.push(to_string(results));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into sub" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
divides two numbers popped from stack and adds to stack
*/
void div(void) {
    globalstack.pop();
    double a, b;
    try {
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();

        double results = b / a;

        globalstack.push(to_string(results));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into div" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
multiplies two numbers popped from stack and adds to stack
*/
void mul(void) {
    globalstack.pop();
    double a, b;
    try {
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();

        double results = a * b;

        globalstack.push(to_string(results));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into mul" << endl;
      


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
divides two integers popped from stack and adds to stack
*/
void idiv(void) {
    globalstack.pop();
    double a, b;
    try {
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();

        double results = b / a;

        globalstack.push(to_string(static_cast<int>(results)));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into idiv" << endl;
        


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
mods two numbers popped from stack and adds to stack
*/
void mod(void) {
    globalstack.pop();
    int a, b;
    try {
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();

        double results = b % a;

        globalstack.push(to_string(results));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into mod" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}
/*
calculate absolute value from number in stack and adds to stack
*/

void abs(void) {
    globalstack.pop();
    double a;
    try {
        a = stof(globalstack.top());
        globalstack.pop();

        if (a < 0) {
            a = a * -1;
        }

        globalstack.push(to_string(a));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into abs" << endl;
        


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
calculate negative value from number in stack and adds to stack
*/
void neg(void) {
    globalstack.pop();
    double a;
    try {
        a = stof(globalstack.top());
        globalstack.pop();

        a = a * -1;

        globalstack.push(to_string(a));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into neg" << endl;
        

    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
determines ceiling of floating point value in stack and pushes result
*/

void ceiling(void) {
    globalstack.pop();
    double a;
    try {
        a = stof(globalstack.top());
        globalstack.pop();

        a = ceil(a);

        globalstack.push(to_string(a));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into ceiling" << endl;
        

    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
determines floor of floating point value in stack and pushes result
*/
void floor(void) {
    globalstack.pop();
    double a;
    try {
        a = stof(globalstack.top());
        globalstack.pop();

        a = floor(a);

        globalstack.push(to_string(a));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into floor" << endl;
        


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
rounds floating point value in stack and pushes result
*/

void round(void) {
    globalstack.pop();
    double a;
    try {
        a = stof(globalstack.top());
        globalstack.pop();

        a = round(a);

        globalstack.push(to_string(a));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into round" << endl;
        

    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
determines square root of value in stack and pushes result
*/

void sqrt(void) {
    globalstack.pop();
    double a;
    try {
        a = stof(globalstack.top());
        globalstack.pop();

        a = sqrt(a);

        globalstack.push(to_string(a));
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into sqrt" << endl;
        


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
swaps two top elements on stack
*/
void exch(void) {
    try {
        globalstack.pop();
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();

        globalstack.pop();

        globalstack.push(s1);
        globalstack.push(s2);
    } 
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into exch" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
copies n values from stack and add it to stack
*/
void copy() {

    globalstack.pop();
    int x;
    vector<string> stackOrder;
    try {
        x = stoi(globalstack.top());
        globalstack.pop();
        if (x > globalstack.size()) {
            cout << "Cannot copy " << x << " elements, too few elements in stack: " << globalstack.size()<<endl;
        }
        else {
            while (x > 0) {
                stackOrder.insert(stackOrder.begin(), globalstack.top());
                globalstack.pop();
                --x;
            }
            for (int y = 0; y < 2; y++) {

                for (string ss : stackOrder) {
                    globalstack.push(ss);
                }
            }
        }

    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into copy" << endl;
            

    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
adds length of string to stack
*/

void length() {
    globalstack.pop();
    string str = globalstack.top();
    try {

        if (str.find("(") == string::npos && str.find("*") == string::npos) {
            cout << "Error, invalid input into length" << endl;

        }
        else {
            if (str.find("(") != string::npos) {
                str = str.substr(2, str.length() - 4);
                globalstack.push(to_string(str.size()));
            }
            else {
                int size = dictmap.size();
                globalstack.push(to_string(size));
            }
            
          
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into length" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
add ascii value of char at position n to stack
*/
void get() {
    globalstack.pop();

    try {
        int x = stoi(globalstack.top());
        globalstack.pop();
        string str = globalstack.top();
        if (str.find("(") != string::npos) {
            str = str.substr(2, str.length() - 4);
            char c = str[x];
            globalstack.push(to_string((int)c));
        }
        else {
            cout << "Error, cannot conduct string operations on non-strings" << endl;

        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into get" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }


}

/*
gets a substring starting at n and getting m values adding it to stack
*/
void getinterval() {
    globalstack.pop();

    try {
        int x = stoi(globalstack.top());
        globalstack.pop();
        int y = stoi(globalstack.top());
        globalstack.pop();
        string str = globalstack.top();
        globalstack.pop();
        if (str.find("(") != string::npos) {
            str = str.substr(2, str.length() - 4);
            string userstring = str.substr(y, y + x - 1);
            globalstack.push(userstring);
        }
        else {
            cout << "Error, cannot conduct string operations on non-strings" << endl;

        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into getinterval" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
replaces substr in range with another string starting at point n
*/
void putinterval() {
    globalstack.pop();

    try {
        string string1 = globalstack.top();
        globalstack.pop();
        int x = stoi(globalstack.top());
        globalstack.pop();
        string string2 = globalstack.top();
        globalstack.pop();
        int i = 0;
        if (string1.find("(") != string::npos && string2.find("(") != string::npos) {
            string1 = string1.substr(2, string1.length() - 4);
            string2 = string2.substr(2, string2.length() - 4);

            for (; i + x < string2.size() && i < string1.size(); i++) {
                
                    string2[i + x] = string1[i];
                

            }
            if (i < string1.length() - 1) {
                string2.append(string1.substr(i, string1.length() - 1));
                globalstack.push(string2);
            }
            else {
                globalstack.push(string2);
            }

        }
        else {
            cout << "Error, cannot conduct string operations on non-strings" << endl;

        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into putinterval" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}



/*
using the "=" operator
*/

void equals() {
    try {
        globalstack.pop();
        string s = globalstack.top();
        if (s.find("(") != string::npos) {
            s = s.substr(2, s.length() - 4);
            cout << s << endl;
        }
        if (s.find("{") != string::npos) {
            s = s.substr(2, s.length() - 4);
        }
        cout << globalstack.top() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into equals" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
defining variable with value and storing in current dictionary on stack
*/
void def() {

    try {
        globalstack.pop();
        string value = globalstack.top();
        globalstack.pop();
        string key = globalstack.top();
        globalstack.pop();

        if (key[0] != '/') {
            cout << "Error, invalid variable name syntax" << endl;
        }
        else {
            if (stoi(dictStack[0]["SIZE_OF_DICTIONARY"]) != -1) {

                if (dictStack[0].size() - 1 == stoi(dictStack[0]["SIZE_OF_DICTIONARY"])) {

                    cout << "Error, exceeding size of dictionary" << endl;

                }
                else {
                    string finalKey = key.substr(1, key.length() - 1);
                    dictStack[0][finalKey] = value;

                }
            }
            else {
                string finalKey = key.substr(1, key.length() - 1);
                dictStack[0][finalKey] = value;
            }

        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into def" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}


/*
duplicates first element on stack
*/
void dup() {
    try {
        globalstack.pop();
        string duplicate = globalstack.top();
        globalstack.push(duplicate);
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into dup" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
using "==" operator
*/
void equalsequals() {
    try {
        globalstack.pop();
        string s = globalstack.top();
        cout << globalstack.top() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into ==" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
prints postscript form of top of stack
*/

void print() {
    try {
        globalstack.pop();
        string s = globalstack.top();
        if (s.find("(") != string::npos) {
            s = s.substr(2, s.length() - 4);
            cout << s << endl;
        }
        else {
            cout << "Error, readable is not a string" << endl;
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into print" << endl;

    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
checks if two top values on stack are equal
*/
void eq() {
    globalstack.pop();
    try {
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();
        globalstack.pop();
        if (s1 == s2) {
            globalstack.push("TRUE");
        }
        else {
            globalstack.push("FALSE");
        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into eq" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}
/*
checks if two top values on stack are not equal
*/
void ne() {
    globalstack.pop();
    try {
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();
        globalstack.pop();
        if (s1 == s2) {
            globalstack.push("FALSE");
        }
        else {
            globalstack.push("TRUE");
        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into ne" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
checks if two top values on stack are greater than or equal
*/
void ge() {
    globalstack.pop();
    try {
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();
        globalstack.pop();
        if (s1.find("(") != string::npos && s2.find("(") != string::npos) {

            if (s2 >= s1) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }
        else {
            int x, y;
            x = stof(s1);
            y = stof(s2);
            if (y >= x) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into ge" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
checks if two top values on stack are greater than
*/
void gt() {
    globalstack.pop();
    try {
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();
        globalstack.pop();
        if (s1.find("(") != string::npos && s2.find("(") != string::npos) {

            if (s2 > s1) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }
        else {
            int x, y;
            x = stof(s1);
            y = stof(s2);
            if (y > x) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into gt" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
checks if two top values on stack are less than or equal
*/
void le() {

    globalstack.pop();
    try {
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();
        globalstack.pop();
        if (s1.find("(") != string::npos && s2.find("(") != string::npos) {

            if (s2 <= s1) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }
        else {
            int x, y;
            x = stof(s1);
            y = stof(s2);
            if (y <= x) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into le" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}
/*
checks if two top values on stack are less than
*/

void lt() {

    globalstack.pop();
    try {
        string s1 = globalstack.top();
        globalstack.pop();
        string s2 = globalstack.top();
        globalstack.pop();
        if (s1.find("(") != string::npos && s2.find("(") != string::npos) {

            if (s2 < s1) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }
        else {
            int x, y;
            x = stof(s1);
            y = stof(s2);
            if (y < x) {
                globalstack.push("TRUE");
            }
            else {
                globalstack.push("FALSE");
            }

        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into lt" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
pushes boolean value of "and" operator 
*/
void andOp() {
    globalstack.pop();
    try {
        
        string statement1 = globalstack.top();
        globalstack.pop();
        string statement2 = globalstack.top();
        globalstack.pop();

        for (char& c : statement1) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        for (char& c : statement2) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        if (statement1 == "true" && statement2 == "true") {
            globalstack.push("TRUE");
        }
        else {
            globalstack.push("FALSE");
        }

    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into and" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
pushes boolean value of "or" operator 
*/

void orOp() {

    globalstack.pop();
    try {

        string statement1 = globalstack.top();
        globalstack.pop();
        string statement2 = globalstack.top();
        globalstack.pop();

        for (char& c : statement1) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        for (char& c : statement2) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }

        if (statement1 == "true" || statement2 == "true") {
            globalstack.push("TRUE");
        }
        else {
            globalstack.push("FALSE");
        }

    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into or" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}


/*
pushes boolean value of "not" operator 
*/
void notOp() {

    globalstack.pop();
    try {

        string statement1 = globalstack.top();
        globalstack.pop();

        for (char& c : statement1) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
  

        if (statement1 == "true") {
            globalstack.push("FALSE");
        }
        else {
            globalstack.push("TRUE");
        }

    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into not" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
carries out given procedure if condition is true
*/

void iff() {

    try {
        globalstack.pop();
        string procedure = globalstack.top();
        globalstack.pop();
        string condition = globalstack.top();

        for (char& c : condition) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }


        if (condition == "false") {


        }
        else if (condition == "true")
        {
            if (procedure.find("{") != string::npos) {

                if (procedure.find("}") != string::npos) {

                    string carryabl1 = procedure.substr(2, procedure.length() - 4);
                    parsing(carryabl1);


                }
                else {
                    cout << "Error: incomplete procedure call" << endl;

                }
            }
            else {
                cout << "Error: incomplete procedure call" << endl;

            }
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into if" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}


/*
carries out given procedure if condition is true or conduct other procedure if false
*/

void iffelse() {

    try {
        globalstack.pop();
        string procedureFalse = globalstack.top();
        globalstack.pop();
        string procedureTrue = globalstack.top();
        globalstack.pop();
        string condition = globalstack.top();
        globalstack.pop();

        for (char& c : condition) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }


        if (condition == "false") {
            if (procedureFalse.find("{") != string::npos) {

                if (procedureTrue.find("}") != string::npos) {

                    string carryabl1 = procedureFalse.substr(2, procedureFalse.length() - 4);
                    parsing(carryabl1);


                }
                else {
                    cout << "Error: incomplete procedure call" << endl;

                }
            }
            else {
                cout << "Error: incomplete procedure call" << endl;

            }

        }
        else if (condition == "true")
        {
            if (procedureTrue.find("{") != string::npos) {

                if (procedureTrue.find("}") != string::npos) {

                    string carryabl1 = procedureTrue.substr(2, procedureTrue.length() - 4);
                    parsing(carryabl1);


                }
                else {
                    cout << "Error: incomplete procedure call" << endl;

                }
            }
            else {
                cout << "Error: incomplete procedure call" << endl;

            }
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into ifelse" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
carries out given procedure for n given iterations
*/
void forF() {
    try {
        globalstack.pop();
        string procedure = globalstack.top();
        globalstack.pop();
        int max = stoi(globalstack.top());
        globalstack.pop();
        int incrementer = stoi(globalstack.top());
        globalstack.pop();
        int min = stoi(globalstack.top());
        globalstack.pop();

        if (procedure.find("{") != string::npos) {

            if (procedure.find("}") != string::npos) {

                string carryabl1 = procedure.substr(2, procedure.length() - 4);
                parsing(carryabl1);

                for (; min < max; min += incrementer) {
                    parsing(carryabl1);

                }


            }
            else {
                cout << "Error: incomplete procedure call" << endl;

            }
        }
        else {
            cout << "Error: incomplete procedure call" << endl;

        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into for" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}

/*
repeats procedure for n iterations
*/
void repeat() {
    try {
        globalstack.pop();
        string procedure = globalstack.top();
        globalstack.pop();
        int times = stoi(globalstack.top());
        globalstack.pop();

        if (procedure.find("{") != string::npos) {

            if (procedure.find("}") != string::npos) {

                string carryabl1 = procedure.substr(2, procedure.length() - 4);
                parsing(carryabl1);

                for (int i = 0; i < times; i++) {
                    parsing(carryabl1);

                }


            }
            else {
                cout << "Error: incomplete procedure call" << endl;

            }
        }
        else {
            cout << "Error: incomplete procedure call" << endl;

        }


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into repeat" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
create a new dict with given size
*/

void dict() {
    try {
        globalstack.pop();
        int m = stoi(globalstack.top());

        string def = "*" + to_string(m) + "*";

        globalstack.pop();
        globalstack.push(def);
        
        
        


    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into dict" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
get max length of the current dict
*/

void maxlength() {
    globalstack.pop();
    string str = globalstack.top();
    try {

        if ( str.find("*") == string::npos) {
            cout << "Error, invalid input into maxlength" << endl;

        }
        else {
            globalstack.push(str.substr(1, str.length() - 2));


        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into maxlength" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}


/*
starts the next dict in stack
*/
void begin() {
    globalstack.pop();
    string str = globalstack.top();
    try {

        if (str.find("*") == string::npos) {
            cout << "Error, invalid input into begin" << endl;

        }
        else {

            dictmap["SIZE_OF_DICTIONARY"] = str.substr(1, str.length() - 2);
            dictStack.insert(dictStack.begin(), dictmap);

        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into begin" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }
}


/*
ends new dict on dict stack (pops it)
*/
void end() {

    globalstack.pop();
    try {

        if (dictStack.size() == 1)
        {
            cout << "Error, cannot delete base dictionary" << endl;
        }
        else {
            dictStack.erase(dictStack.begin());
        }
    }
    catch (const invalid_argument& e) {
        cout << "Error, invalid input into end" << endl;


    }
    catch (const out_of_range& e) {
        cout << "Error, out of bounds" << endl;
    }

}

/*
calls a function that is custom (not empty value in key:value)
*/
void nonemptyCommand(string currentCommand, vector <string>& s, int& j) {
    globalstack.pop(); // pop name from stack 

    string carryable = dictStack[currentDictStack][currentCommand]; //get the value from dict

    if (carryable.find("{") != std::string::npos) { // if it is a procedure

        string carryabl1 = carryable.substr(2, carryable.length() - 4); //parse out "{}"

        vector <string> s1 = splittingString(carryabl1, " "); //split procedure to add to stack

        s.insert(s.begin() + j + 1, s1.begin(), s1.end());//insert proc into vector string to replace name
        s.erase(s.begin() + j); //erase name


        --j;
    }

    else { // is a value

        s.insert(s.begin() + j + 1, carryable);
        s.erase(s.begin() + j);
        --j;
    }
}

/*
calls built in commands in dict

*/

void call_command_on_stack(string currentCommand) {

    if (currentCommand == "add") {
        if (globalstack.size() < 3) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            add();
        }

    }
    if (currentCommand == "sub") {
        if (globalstack.size() < 3) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            sub();
        }
    }
    if (currentCommand == "div") {
        if (globalstack.size() < 3) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            div();
        }
    }
    if (currentCommand == "mul") {
        if (globalstack.size() < 3) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            mul();
        }
    }
    if (currentCommand == "idiv") {
        if (globalstack.size() < 3) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            idiv();
        }
    }
    if (currentCommand == "mod") {
        if (globalstack.size() < 3) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            mod();
        }
    }
    if (currentCommand == "abs") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            abs();
        }
    }
    if (currentCommand == "neg") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            neg();
        }
    }
    if (currentCommand == "ceiling") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            ceiling();
        }
    }
    if (currentCommand == "floor") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            floor();
        }
    }
    if (currentCommand == "round") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            round();
        }
    }
    if (currentCommand == "sqrt") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            sqrt();
        }
    }
    if (currentCommand == "exch") {
        if (globalstack.size() < 2) {
            globalstack.pop();

            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {

            exch();
        }
    }
    if (currentCommand == "pop") {
        if (globalstack.size() < 2) {
            globalstack.pop();
            cout << "Error, not enough values in stack to compute" << endl;

        }
        else {
            globalstack.pop();
            globalstack.pop();


        }
    }
    if
        (currentCommand == "def") {
        if (globalstack.size() < 2) {
            globalstack.pop();
            cout << "Error, not enough values in stack to compute" << endl;
        }
        else {
            def();
        }
        


    }
    if (currentCommand == "=") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();

        }
        else {
            equals();
        }

    }
    if (currentCommand == "==") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();

        }
        else {
            equalsequals();
        }

    }
    if (currentCommand == "copy") {
        copy();
    }
    if (currentCommand == "dup") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();

        }
        else {
            dup();

        }

    }
    if (currentCommand == "clear") {
        while (!globalstack.empty()) {
            globalstack.pop();
        }
    }
    if (currentCommand == "count") {
        globalstack.pop();
        globalstack.push(to_string(globalstack.size()));
    }
    if (currentCommand == "length") {
        

        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;

        }
      
        else {

            length();
        }

    }
    if (currentCommand == "get") {
        
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            get();
        }

    }
    if (currentCommand == "getinterval") {
        if (globalstack.size() < 4) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            getinterval();
        }
    }
    if (currentCommand == "putinterval") {
        if (globalstack.size() < 4) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }

        else {
            putinterval();
        }
    }
    if (currentCommand == "print") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();

        }
        else {
            print();
        }
    }
    if (currentCommand == "eq") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            eq();

        }

    }
    if (currentCommand == "ne") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            ne();

        }
    }
    if (currentCommand == "ge") {

        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            ge();

        }

    }
    if (currentCommand == "gt") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            gt();

        }
    }
    if (currentCommand == "le") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            le();

        }
    }
    if (currentCommand == "lt") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            lt();

        }

    }
    if (currentCommand == "and") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            andOp();

        }
    }
    if (currentCommand == "or") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            orOp();

        }
    }
    if (currentCommand == "not") {
        if (globalstack.size() < 1) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            notOp();

        }
    }
    if (currentCommand == "if") {
        if (globalstack.size() < 3) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            iff();
        }
    }if (currentCommand == "ifelse") {
        if (globalstack.size() < 4) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            iffelse();
        }
    }
    if (currentCommand == "for") {
        if (globalstack.size() < 5) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            forF();
        }
    }
    if (currentCommand == "repeat") {
       if (globalstack.size() < 3) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            repeat();
        } 
    }
    if (currentCommand == "dict") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            dict();
        }
    }
    if (currentCommand == "maxlength") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            maxlength();
        }
    }
    if (currentCommand == "begin") {
        if (globalstack.size() < 2) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            begin();
        }
    }
    if (currentCommand == "end") {
        if (globalstack.size() < 1) {
            cout << "Error, not enough variables on stack to compute" << endl;
            globalstack.pop();
        }
        else {
            end();
        }
    }

    
    


}

/*
populates the first dict with base functions and empty values for later conditional checking
*/
void populate_function_map(void) {
    functionMap["SIZE_OF_DICTIONARY"] = "-1";
    functionMap["add"] = " ";
    functionMap["sub"] = " ";
    functionMap["div"] = " ";
    functionMap["mul"] = " ";
    functionMap["idiv"] = " ";
    functionMap["mod"] = " ";
    functionMap["abs"] = " ";
    functionMap["neg"] = " ";
    functionMap["ceiling"] = " ";
    functionMap["floor"] = " ";
    functionMap["round"] = " ";
    functionMap["sqrt"] = " ";
    functionMap["exch"] = " ";
    functionMap["pop"] = " ";
    functionMap["copy"] = " ";
    functionMap["def"] = " ";
    functionMap["="] = " ";
    functionMap["dup"] = " ";
    functionMap["clear"] = " ";
    functionMap["count"] = " ";
    functionMap["length"] = " ";
    functionMap["get"] = " ";
    functionMap["getinterval"] = " ";
    functionMap["putinterval"] = " ";
    functionMap["print"] = " ";
    functionMap["eq"] = " ";
    functionMap["ne"] = " ";
    functionMap["ge"] = " ";
    functionMap["gt"] = " ";
    functionMap["le"] = " ";
    functionMap["lt"] = " ";
    functionMap["and"] = " ";
    functionMap["or"] = " ";
    functionMap["not"] = " ";
    functionMap["true"] = " ";
    functionMap["false"] = " ";
    functionMap["if"] = " ";
    functionMap["ifelse"] = " ";
    functionMap["for"] = " ";
    functionMap["repeat"] = " ";
    functionMap["dict"] = " ";
    functionMap["maxlength"] = " ";
    
    functionMap["begin"] = " ";
    functionMap["end"] = " ";



   
   

    dictStack.insert(dictStack.begin(), functionMap); // insert into stack

}

//prettify input
string getting_line(void) {
    string x;
    cout << "REPL> ";

    getline(cin, x, '\n');
    return x;
}


/*
formats array for consistent popping and using from stack
*/
string array_check(int& j, vector <string>& s) {
    string arra;
    int check = -1;

    if (s[j].length() > 1 && s[j].find("]") != string::npos) { //if array is a single element with no spaces eg [1]
        string first_element = s[j].substr(1, s[j].length() - 2);
        arra += "[";
        arra += " "; //add spaces between bracket and element
        arra += first_element;
        arra += " ";
        arra += "]";
        check = 0;
        ++j;

    }
    if (s[j].length() > 1) { //if first array element is not separated from the bracket, eg [1 2 ]
        string first_element = s[j].substr(1, s[j].length() - 1);
        arra += "[";
        arra += " ";
        arra += first_element;
        arra += " ";
        ++j;
    }
    while (check == -1) { //while closing bracket hasnt been found
        while (s[j].find("]") == string::npos && j < s.size()) { //while there is still string to parse
            arra += s[j];
            arra += " ",
                ++j;

        }
        if (j == s.size()) { //if this string doesnt have the bracket, the next elements and bracket comes on next line
            string x = getting_line();
            s = splittingString(x, " ");
            j = 0;

        }
        else {
            check = 0; //implies ] is found in string
            if (s[j].length() > 1) {
                string first_element = s[j].substr(0, s[j].length() - 1); //if closing bracket is connected to final string
                arra += first_element;
                arra += " ";
                arra += "]";
                ++j;
            }
            else {
                arra += s[j];
                ++j;
            }
        }
    }

    return arra;
}

//does the same steps as array_check does, just with brackets {}
string procedure_check(int& j, vector <string>& s) {
    string proc;
    int check = -1;
    if (s[j].length() > 1 && s[j].find("}") != string::npos) {
        string first_element = s[j].substr(1, s[j].length() - 2);
        proc += "{";
        proc += " ";
        proc += first_element;
        proc += " ";
        proc += "}";
        check = 0;
        ++j;

    }
    if (s[j].length() > 1) {
        string first_element = s[j].substr(1, s[j].length() - 1);
        proc += "{";
        proc += " ";
        proc += first_element;
        proc += " ";
        ++j;
    }


    while (check == -1) {
        while (s[j].find("}") == string::npos && j < s.size()) {
            proc += s[j];
            proc += " ",
                ++j;

        }
        if (j == s.size()) {
            string x = getting_line();
            s = splittingString(x, " ");
            j = 0;

        }
        else {
            check = 0;
            if (s[j].length() > 1) {
                string first_element = s[j].substr(0, s[j].length() - 1);
                proc += first_element;
                proc += " ";
                proc += "}";
                ++j;
            }
            else {
                proc += s[j];
                ++j;
            }



        }
    }
    return proc;

}


//does the same steps as array_check does, just with parenthesis

string string_check(int& j, vector <string>& s) {
    string proc;
    int check = -1;

    if (s[j].length() > 1 && s[j].find(")") != string::npos) {
        string first_element = s[j].substr(1, s[j].length() - 2);
        proc += "(";
        proc += " ";
        proc += first_element;
        proc += " ";
        proc += ")";
        check = 0;
        ++j;
    }

    else if (s[j].length() > 1) {
        string first_element = s[j].substr(1, s[j].length() - 1);
        proc += "(";
        proc += " ";
        proc += first_element;
        proc += " ";
        ++j;
    }



    while (check == -1) {
        while (s[j].find(")") == string::npos && j < s.size()) {
            proc += s[j];
            proc += " ",
                ++j;

        }
        if (j == s.size()) {
            string x = getting_line();
            s = splittingString(x, " ");
            j = 0;

        }
        else {
            check = 0;
            if (s[j].length() > 1) {
                string first_element = s[j].substr(0, s[j].length() - 1);
                proc += first_element;
                proc += " ";
                proc += ")";
                ++j;
            }
            else {
                proc += s[j];
                ++j;
            }



        }
    }
    return proc;
}


//parsing each input string
void parsing(string x) {
    string currentCommand = "\0"; 

    vector<string> s = splittingString(x, " "); //get string
    int j = 0; //position in vector
    int check = -1;

    while (j < s.size()) { // while not at end of vector
        currentCommand = "\0"; //reset values for each string
        currentDictStack = 0;
        check = -1;


        if (s[j].find("[") != std::string::npos) { //if its an array, parse accordingly
            string arra = array_check(j, s);
            globalstack.push(arra);
        }
        else if (s[j].find("{") != std::string::npos) { //if its a proc, parse accordingly
            string sequence = procedure_check(j, s);
            globalstack.push(sequence);

        }
        else if (s[j].find("(") != std::string::npos) { //if its a string, parse accordingly
            string str = string_check(j, s);
            globalstack.push(str);
        }
        else if (s[j].find("/") != string::npos) { // if new variable, add to stack
            globalstack.push(s[j]);
            ++j;
        }
        else if (s[j] == "***"){
            staticvar = !staticvar;
            ++j;
        }
        
        else {
            for (char& c : s[j]) { // reduce error by casting string to lowercase
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
                }

            if (staticvar == false) { // if in dynamic mode
                for (size_t i = 0; i < dictStack.size() && check == -1; ++i) {//automatically check every member of stack

                    if (dictStack[i].find(s[j]) != dictStack[i].end()) {// if command is in this dict
                        
                        currentCommand = s[j]; //set current command
                        globalstack.push(s[j]); //pushes command onto stack
                        check = 1; //command is found validator

                        if (dictStack[i][currentCommand] != " ") { //nonempty function, this must be parsed from dict
                            currentDictStack = i;

                            nonemptyCommand(currentCommand, s, j); 

                        }
                        else {    // if empty, it is a base function
                            call_command_on_stack(currentCommand);
                        }


                    }

                }
            }
            else { //if in static mode

                if (dictStack[0].find(s[j]) != dictStack[0].end()) { //look in current dict

                    currentCommand = s[j];
                    globalstack.push(s[j]);
                    check = 1;

                    if (dictStack[0][currentCommand] != " ") { //nonempty function, this must be parsed from dict
                        currentDictStack = 0;

                        nonemptyCommand(currentCommand, s, j);

                    }
                    else {
                        call_command_on_stack(currentCommand);
                    }


                }
                else if (dictStack.back().find(s[j]) != dictStack.back().end()) //check base stack
                {
                    currentCommand = s[j];
                    globalstack.push(s[j]);
                    check = 1;

                    if (dictStack.back()[currentCommand] != " ") {//nonempty function, this must be parsed from dict
                        currentDictStack = dictStack.size() - 1;

                        nonemptyCommand(currentCommand, s, j);

                    }
                    else {
                        call_command_on_stack(currentCommand);
                    }

                }

            }
            if (check == -1) { //the value was not found
                try{
                    size_t pos;
                    stod(s[j], &pos); //check if it is a floating point number

                    globalstack.push(s[j]);
                
                
                
                }
                catch (const invalid_argument& e) { // will throw error if not number
                    cout << "Error, invalid input into stack" << endl;


                }
                catch (const out_of_range& e) {
                    cout << "Error, out of bounds" << endl;
                }
            }
            

            ++j;

        }


    }



}

