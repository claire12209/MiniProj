# Mini Project

Assignment 4 : Implementing a PostScript Interpreter - Mini Project

## Description

A fully functional postscript interpreter that can interpret the given subset of commands. The repo also contains a tests simulation to test all base command functions 
and their outliers

## Getting Started

### Dependencies

* Ubuntu 22.04 or higher
* C/C++ interpreter
* Google Test
  
     install library ```sudo apt install libgtest-dev```

## Executing Interpreter

* enter directory containing .cpp and .h files
* run command ``` g++ miniproj.cpp -o miniproj ``` to generate the .o files
* run command ``` ./miniproj ``` to start the interpreter 
   #### Dynamic vs Static
    * when starting the program, the typing will be dynamic automatically
    * to switch to static typing, enter command
      ```  REPL> *** ```
    * The command allows switching between dynamic and static typing as the interpreter runs

## Executing Tests
* enter directory containing .cpp and .h files
* run command ``` g++ -std=c++11 tests.cpp -o my_test -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main -lpthread``` to generate .o files and access testing library
* run command ```./my_test``` to run all tests



### 
