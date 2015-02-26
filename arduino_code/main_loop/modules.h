#ifndef MODULES_H
#define MODULES_H

#include "defines.h"

// ********************
// processing modules *
// ********************

// for help with function pointers see this link:
// http://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work

// -> GENERIC
// this will be the generic format for each module struct
// to be used as a place holder for compiler when calling arbitrary modules 
typedef struct generic_struct* generic;
// struct
struct generic_struct {
  // function
  void (*proc)(generic self, param genericParam);
  // data
  void* structData; // pointer to an array of all inputs/outputs/data for each module
};

// -> DELAY LINE
typedef struct delay_line_struct* delay_line;
#define MIN_DELAY 800
// struct
struct delay_line_struct {
  // functions
  void (*proc)(delay_line self, param paramDelay); // pointer to function that actually performs the delay
  // data
  sample* input;    // pointer to the input sample to the delay line
  sample* output;   // pointer to the output sapmple of the delay line
  sample* buffHead;     // a buffer that is the length of the maximum number of samples that can be delayed
  unsigned int len; // the length of the buffer
  sample* buffPos;  // points to the current buffer position
};
// internal funcs
void proc_delay_line(delay_line self, param paramDelay); // function that actually performs the delay
// external funcs
delay_line new_delay_line(sample* in, sample* out, unsigned int maxLen); // instantiates a new delay_line struct (I will call them objects)

// -> GAIN
typedef struct gain_struct* gain;
#define LINEAR 0
#define LOG 1
// struct
struct gain_struct {
  // functions
  void (*proc)(gain self, param paramGain);
  // data
  sample* input;          // pointer to the input sample to the delay line
  sample* output;         // pointer to the output sapmple of the delay line
  unsigned short maxGain; // maximum gain of block
  bool linlog;            // decides whether block will have linear/log curve
};
// internal funcs
void proc_gain(gain self, param paramGain); 
// external funcs 
gain new_gain(sample* in, sample* out, unsigned short maxGain, bool type);

// -> SUMMER
typedef struct summer_struct* summer;
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
summer new_summer(sample* inOne, sample* inTwo, sample* out);

#endif