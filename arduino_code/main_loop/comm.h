#ifndef COMM_H
#define COMM_H

#include "defines.h"

// defines
// communication flags
#define READY 128

// globals
int numMods; // number of modules in effect
// for the following arrays, the array index corresponds to an individual module
// length = numMods for each array
int* modIDList;   // array of module IDs
generic* modList; // array of pointers to modules
int* inList;      // array of module net inputs
int* outList;     // array of module net outputs

int numNets; // number of nets in effect
// for the following arrays, the array index corresponds to an individual net
// length = number of nets for each for each index
sample** netList; // array of pointers to samples

int numArgs; // number of total arguments for all modules in effect
// for the following arrays, the array index corresponds to an individual argument
// length = number of arguments for each array
int* argList; // array containing all arguments for each module
int** parsedArgList; // 2d array where each row corresponds to a single module

// function prototypes
sample** inst_nets(int num);                         // instantiates each net sample
void get_serial_data(void);                          // function that communicates with web app

// num = number of modules
// list = straight list
// IDlist = list of module IDs
int** parse_args(int num, int* list, int* IDlist);   // takes a straight list of parameters and converts it to a parsed list

#endif
