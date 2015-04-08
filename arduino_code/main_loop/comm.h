#ifndef COMM_H
#define COMM_H

#include "defines.h"

// globals
int numMods;   // number of modules in effect
// for the following arrays, the array index corresponds to an individual module
// length = numMods for each array
int* modIDList;   // array of module IDs
generic* modList; // array of pointers to modules
int* inList;      // array of module net inputs
int* outList;     // array of module net outputs

int numNets;      // number of nets in effect
// for the following arrays, the array index corresponds to an individual net
// length = number of nets for each for each index
sample** netList; // array of pointers to samples

int numArgs;         // number of total arguments for all modules in effect
// for the following arrays, the array index corresponds to an individual argument
// length = number of arguments for each array
int* argList;        // array containing all arguments for each module
int** parsedArgList; // 2d array where each row corresponds to a single module

int*  paramIDList;    // array containing the param type for each module
int*  paramList;      // array containing the actual param for each module from web app
param** paramPtrList; // array of pointers to actual params that are passed to modules

// function prototypes
sample** inst_nets(void);          // instantiates each net sample
void parse_serial_data(int* list); // function that parses list from web app
void check_comm(void);             // checks if there is serial data available, calls parser function if so

// helper function prototypes

// num = number of modules
// list = straight list
// IDlist = list of module IDs
int** parse_args(int num, int* list, int* IDlist);           // takes a straight list of parameters and converts it to a parsed list

int* get_serial_data(void);                                  // if serial data available, gets it and stores it in an array, returns pointer to array, also writes array to flash

// list = main list to parse from
// num = number of elements to parse
// currIndexPtr = pointer to current index the main list
int* parse_main_list(int* list, int num, int* currIndexPtr); // takes in a main list and parses a chunk of it into a smaller list, returns pointer to smaller list

param** create_param_ptrs(void);

#endif
