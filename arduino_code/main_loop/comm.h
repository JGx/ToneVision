#ifndef COMM_H
#define COMM_H

#include "defines.h"

// globals
int numMods; // number of modules in effect
// for the following arrays, the array index corresponds to an individual module
// length = numMods for each array
int* modIDList;  // array of module IDs
//generic modList; // array of pointers to modules
int* inList;     // array of module net inputs
int* outList;    // array of module net outputs

int numNets; // number of nets in effect
// for the following arrays, the array index corresponds to an individual net
// length = number of nets for each for each index
sample** netList; // array of pointers to samples

int numParams; // number of total parameters for all modules in effect
// for the following arrays, the array index corresponds to an individual parameter
// length = number of parameters for each array
int* paramList; // array containing all parameters for each module
int** parsedParamList; // 2d array where each row corresponds to a single module

// function prototypes
generic inst_modules(int num, int* list);            // instatiates each module
sample** inst_nets(int num);                         // instantiates each net sample
// num = number of modules
// list = straight list
// IDlist = list of module IDs
int** parse_params(int num, int* list, int* IDlist); // takes a straight list of parameters and converts it to a parsed list

#endif
