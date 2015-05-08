#ifndef MODULES_H
#define MODULES_H

#include "defines.h"
#include "filterLUTs.h"
#include "gainLUTs.h"

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
#define DELAY_K 0.01
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
  int prevParam;    // previous parameter reading
  sample* buffPos;  // points to the current buffer position
};
// internal funcs
void proc_delay_line(delay_line self, param* paramDelay); // function that actually performs the delay
// external funcs
generic new_delay_line(sample* in, sample* out, unsigned int minLen, unsigned int maxLen); // instantiates a new delay_line struct (I will call them objects)

// -> GAIN
typedef struct gain_struct* gain;
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

// -> ENVELOPE FOLLOWER
typedef struct env_struct* env;
#define ENV_BUFF_LEN 2
#define ENV_K 0.00005
// struct
struct env_struct {
  // functions
  void (*proc)(env self);
  // data
  sample* input;    // pointer to input sample
  param* output;    // pointer to output control signal
  float currIn;     // current input
  float prevOut;    // previous output
};
// internal funcs
void proc_env(env self);
// external funcs
generic new_env(sample* in, param* out);

// -> FILTER
typedef struct filter_struct* filter;

// struct
struct filter_struct {
  // functions
  void (*proc)(filter self, param* cutoff);
  // data
  sample* input;    // pointer to input sample
  param* output;    // pointer to output control signal
  int currIn;       // current input sample
  int currOut;      // current output sample
  int inBuff1;      // input buffer
  int inBuff2;    
  int outBuff0;     // output buffer
  int outBuff1;
};
// internal funcs
void proc_filter(filter self, param* cutoff);
// external funcs
generic new_filter(sample* in, param* out);

// *************
// * CONSTANTS *
// *************

// constants


#endif
