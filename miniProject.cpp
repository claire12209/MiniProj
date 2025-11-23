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

using namespace std; 
stack <string> globalstack;
std::map<std::string, string> functionMap;
vector<std::map<std::string, string>> dictStack;

bool staticvar = false;
int currentDictStack = 0;

vector <string> splittingString(const string & s, const string &delim){
    vector <string> substringVector;
    size_t begin = 0;
    size_t end = s.find(delim);
    while (end != string::npos){
        substringVector.push_back(s.substr(begin, end - begin));
        begin = end + delim.length();
        end = s.find(delim, begin);

    }
    substringVector.push_back(s.substr(begin));
    return substringVector;
}

void add(void){
    globalstack.pop();
    double a,b;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();
                        
        double results = a+b;
        cout<<"in add"<<endl;

        globalstack.push(to_string(results));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into add"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }
}
void sub(void){
globalstack.pop();
    double a,b;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();
                        
        double results = b-a;
        cout<<results<<endl;

        globalstack.push(to_string(results));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into sub"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }

}
void div(void){
    globalstack.pop();
    double a,b;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();
                        
        double results = b/a;
        cout<<results<<endl;

        globalstack.push(to_string(results));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into div"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}

void mul(void){
    globalstack.pop();
    double a,b;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();
                        
        double results = a*b;
        cout<<results<<endl;

        globalstack.push(to_string(results));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into mul"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}
void idiv(void){
    globalstack.pop();
    double a,b;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();
                        
        double results = b/a;
        cout<<static_cast<int>(results)<<endl;

        globalstack.push(to_string(static_cast<int>(results)));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into idiv"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}
void mod(void){
    globalstack.pop();
    int a,b;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        b = stof(globalstack.top());
        globalstack.pop();
                        
        double results = b%a;
        cout<<results<<endl;

        globalstack.push(to_string(results));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into mod"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}

void abs(void){
    globalstack.pop();
    double a;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
                        
        if(a < 0){
            a = a * -1;
        }
        cout<<a<<endl;

        globalstack.push(to_string(a));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into abs"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}

void neg(void){
    globalstack.pop();
    double a;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        
        a = a * -1;
        cout<<a<<endl;

        globalstack.push(to_string(a));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into neg"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}


void ceiling(void){
    globalstack.pop();
    double a;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        
        a = ceil(a);
        cout<<a<<endl;

        globalstack.push(to_string(a));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into ceiling"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}

void floor(void){
    globalstack.pop();
    double a;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        
        a = floor(a);
        cout<<a<<endl;

        globalstack.push(to_string(a));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into floor"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}

void round(void){
    globalstack.pop();
    double a;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        
        a = round(a);
        cout<<a<<endl;

        globalstack.push(to_string(a));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into round"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}

void sqrt(void){
    globalstack.pop();
    double a;
    try{
        a = stof(globalstack.top());
        globalstack.pop();
        
        a = sqrt(a);
        cout<<a<<endl;

        globalstack.push(to_string(a));
        }catch (const invalid_argument & e){
            cout<<"Error, invalid input into sqrt"<<endl;
            globalstack.pop();
            globalstack.pop();


        }catch(const out_of_range & e){
            cout<<"Error, out of bounds"<<endl;
            }


}
void exch(void){
    globalstack.pop();
    string s1 = globalstack.top();
    globalstack.pop();
    string s2 = globalstack.top();

    globalstack.pop();

    globalstack.push(s1);
    globalstack.push(s2);

   

}

void print_whole_stack(){
    while (!globalstack.empty()){
        cout<<globalstack.top()<<endl;
        globalstack.pop();
    }
}

void call_command_on_stack(string currentCommand, vector <string> & s, int &j){
        
            if( dictStack[currentDictStack][currentCommand] != " "){
                globalstack.pop();
                string carryable = dictStack[currentDictStack][currentCommand];
                if (carryable.find("{") != std::string::npos){
                    string carryabl1 = carryable.substr(2, carryable.length() - 4);
                    vector <string> s1 = splittingString(carryabl1, " ");

                   auto pos = s.begin() + j;
                   s.erase(pos);
                   s.insert(pos, s1.begin(), s1.end());
                    for (string element : s1) {
                    std::cout << element << endl;
                        }

                    --j;
                }
                



            }
            if (currentCommand == "add"){
                if (globalstack.size() < 3){
                    globalstack.pop();

                    cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    add();
                }

            }
            if(currentCommand == "sub"){
                if (globalstack.size() < 3){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    sub();
                }
            }
            if(currentCommand == "div"){
                if (globalstack.size() < 3){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    div();
                }
            }
            if(currentCommand == "mul"){
                if (globalstack.size() < 3){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    mul();
                }
            }
            if(currentCommand == "idiv"){
                if (globalstack.size() < 3){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    idiv();
                }
            }
            if(currentCommand == "mod"){
                if (globalstack.size() < 3){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    mod();
                }
            }
            if(currentCommand == "abs"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    abs();
                }
            }
            if(currentCommand == "neg"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    neg();
                }
            }
            if(currentCommand == "ceiling"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    ceiling();
                }
            }
            if(currentCommand == "floor"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    floor();
                }
            }
            if(currentCommand == "round"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    round();
                }
            }
            if(currentCommand == "sqrt"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    sqrt();
                }
            }
            if(currentCommand == "exch"){
                if (globalstack.size() < 2){
                        globalstack.pop();

                        cout<<"Error, not enough values in stack to compute"<<endl;
                }
                else{
                        
                    exch();
                }
            }
            if (currentCommand == "pop"){
                if (globalstack.size() < 1){
                    globalstack.pop();
                    cout<<"Error, not enough values in stack to compute"<<endl;

                }
                else{
                    globalstack.pop();
                    globalstack.pop();


                }
            }
            if 
            (currentCommand == "def"){
                if (globalstack.size() < 2){
                    globalstack.pop();
                    cout << "Error, not enough values in stack to compute"<<endl;
                }
                globalstack.pop();
                string value = globalstack.top();
                globalstack.pop();
                string key = globalstack.top();
                globalstack.pop();

                if (key[0] != '/'){
                    cout << "Error, invalid variable name syntax"<<endl;
                }
                else{
                    string finalKey = key.substr(1, key.length()-1);
                    dictStack[0][finalKey] = value;

                }


            }

            
            
        }


void populate_function_map(void){
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

     dictStack.insert(dictStack.begin(), functionMap);

}

string getting_line(void){
    string x;
    cout<< "REPL> ";
    
    getline(cin,x, '\n');
    return x;
}



string array_check(int & j, vector <string> &s){
    string arra;
    int check = -1;
    while (check == -1){
        while(s[j].find("]") == string::npos && j < s.size()){
            arra += s[j];
            arra += " ",
            ++j;
            
        }
        if (j == s.size()){
            string x = getting_line();
            s =  splittingString(x, " ");
            j = 0 ;
            
        }
        else{
            check = 1;
            arra+= s[j] ;
            ++j;
            
        }
}                
    
    return arra;
}

string procedure_check(int & j, vector <string> &s){
    string proc;
    int check = -1;

    if (s[j].length() > 1){
        string first_element = s[j].substr(1, s[j].length() -1);
        proc += "{";
        proc += " ";
        proc += first_element;
        proc += " ";
        ++j;
    }


    while (check == -1){
        while(s[j].find("}") == string::npos && j < s.size()){
            proc += s[j];
            proc += " ",
            ++j;
            
        }
        if (j == s.size()){
            string x = getting_line();
            s =  splittingString(x, " ");
            j = 0 ;
            
        }
        else{
            check = 0;
                if (s[j].length() > 1){
                    string first_element = s[j].substr(0, s[j].length() -1);
                    proc += first_element;
                    proc += " ";
                    proc += "}";
                    ++j;
                }
                else{
                    proc+= s[j]; 
                     ++j;
                    }
            
            
           
        }
    }                
    cout<<proc << endl;
    return proc;

}

void parsing(string x){
    string currentCommand = "\0";

    vector<string> s = splittingString(x, " ");
    int j = 0;
    int check = -1;
    while (j < s.size()){
        currentCommand = "\0";
        check = -1;
        if(s[j].find("[") != std::string::npos){
            string arra = array_check(j, s);
            globalstack.push(arra);
        }
        if(s[j].find("{") != std::string::npos){
            string sequence = procedure_check(j, s);
            globalstack.push(sequence);

        }
        
        else{
        for (size_t i = 0; i < dictStack.size(); ++i) {
            if(dictStack[i].find(s[j]) != dictStack[i].end()){
                if(i == 0){
                currentCommand = s[j];
                globalstack.push(s[j]);
                check = 1;
                call_command_on_stack(currentCommand, s, j);
                 if(!globalstack.empty()){
            } 
            else{cout<<"Global Stack is empty" << endl;}
                }
                else{

                }
                    
            }
                
        }
        if (check == -1){
            globalstack.push(s[j]); 

        }
            if(!globalstack.empty()){
            cout<<"Top of stack is outer: " <<globalstack.top()<<endl << "J is at: " << j  << "size is at "<< s.size()<< endl;
            } 
         ++j;
         
        }    

            
    }
            
            
        
}


int main(){
    bool end = true;
    string arr[18] = {"add", "sub", "div", "mul", "idiv", "mod", "abs", "neg", "ceiling", "floor", "round", "sqrt", "exch","pop", "copy", "dup", "clear", "count"};

    populate_function_map();
    
    while (end){
        string x = getting_line();
        if (x == "quit"){
            end = false;
        }
        else{
            parsing(x);
        }
            
            
    }

    return 0;
}