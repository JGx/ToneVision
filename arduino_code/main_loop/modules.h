#ifndef MODULES_H
#define MODULES_H

#include "defines.h"

// general functions
void inst_modules(void); // given all comm data, instantiates each module

// **********************
// * PROCESSING MODULES *
// **********************

// for help with function pointers see this link:
// http://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work

// -> GENERIC
// this will be the generic format for each module struct
// to be used as a place holder for compiler when calling arbitrary modules 
// when each module is created, it will have a generic pointer
// the module will be called from that generic pointer
typedef struct generic_struct* generic;
// struct
struct generic_struct {
  // function
  void (*proc)(generic self, param* genericParam);
  // data
  void* structData; // pointer to an array of all inputs/outputs/data for each module
};

generic new_generic(id modID, sample* in, sample* out, int* list);

// -> DELAY LINE
typedef struct delay_line_struct* delay_line;
#define DELAY_ID 0
#define NUM_DELAY_ARGS 2 // number of arguments to new_delay_line func (not including sample in and out)
// struct
struct delay_line_struct {
  // functions
  void (*proc)(delay_line self, param* paramDelay); // pointer to function that actually performs the delay
  // data
  sample* input;    // pointer to the input sample to the delay line
  sample* output;   // pointer to the output sapmple of the delay line
  sample* buffHead; // a buffer that is the length of the maximum number of samples that can be delayed
  int minDelay;     // minimum delay length
  int len;          // the length of the buffer
  sample* buffPos;  // points to the current buffer position
};
// internal funcs
void proc_delay_line(delay_line self, param* paramDelay); // function that actually performs the delay
// external funcs
generic new_delay_line(sample* in, sample* out, unsigned int minLen, unsigned int maxLen); // instantiates a new delay_line struct (I will call them objects)

// -> GAIN
typedef struct gain_struct* gain;
#define GAIN_ID 1
#define NUM_GAIN_ARGS 2
#define LINEAR 0
#define LOG 1
// struct
struct gain_struct {
  // functions
  void (*proc)(gain self, param* paramGain);
  // data
  sample* input;          // pointer to the input sample to the delay line
  sample* output;         // pointer to the output sapmple of the delay line
  unsigned short maxGain; // maximum gain of block
  bool linlog;            // decides whether block will have linear/log curve
};
// internal funcs
void proc_gain(gain self, param* paramGain); 
// external funcs 
generic new_gain(sample* in, sample* out, unsigned short maxGain, bool type);

// -> SUMMER
typedef struct summer_struct* summer;
#define SUMMER_ID 2
#define NUM_SUMMER_ARGS 1 // this 1 argument is the second sample to be summed, treat it as netList index
// struct
struct summer_struct {
  // functions
  void (*proc)(summer self);
  // data
  sample* inputOne; // pointer to first input sample to sum
  sample* inputTwo; // pointer to other input sample to sum
  sample* output;   // point to output sample
};
// internal funcs
void proc_summer(summer self);
// external funcs
generic new_summer(sample* inOne, sample* out, int inTwoIndex);

#define TOTAL_NUM_MODULES 3 // the total number of modules available
// global array that lists the number of arguments for each module
const int NUMARGSLIST[TOTAL_NUM_MODULES] = {NUM_DELAY_ARGS, NUM_GAIN_ARGS, NUM_SUMMER_ARGS};

#endif
