#ifndef DEFINES_H
#define DEFINES_H

// typedefs
typedef short sample;        // type for each audio sample
typedef unsigned char uint8; // generic
typedef short param;         // type for input parameters to functions
typedef int genericParam;    // type of parameter lists
typedef unsigned short id;   // type for module ID numbers

// defines
#define TOTAL_NUM_MODULES 5 // the total number of modules available

// module type IDs
#define DELAY_ID  0
#define GAIN_ID   1
#define SUMMER_ID 2
#define ENV_ID    3
#define FILTER_ID 4

// number of instantiation arguments for each module (not including in and out pointers)
#define NUM_DELAY_ARGS  2
#define NUM_GAIN_ARGS   2
#define NUM_SUMMER_ARGS 1
#define NUM_ENV_ARGS    0
#define NUM_FILTER_ARGS 0

// parameter type IDs
#define PARAM_STATIC_ID 0 // module takes hardcoded param
#define PARAM_NET_ID    1 // module takes a net value as a param
#define PARAM_KNOB_ID   2 // module takes a knob as a param
#define PARAM_NONE_ID   3 // module doesn't take a param

// global array that lists the number of arguments for each module
const int NUMARGSLIST[TOTAL_NUM_MODULES] = {NUM_DELAY_ARGS,NUM_GAIN_ARGS,NUM_SUMMER_ARGS,NUM_ENV_ARGS,NUM_FILTER_ARGS};

// globals
sample* currInSamplePtr; // points to current sample
sample* currOutSamplePtr;
bool fatalError;

#endif
