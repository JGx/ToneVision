#ifndef DAC_H
#define DAC_H
  
#include "defines.h"
  
// analog outputs
#define OUT_DAC DAC1

// functions prototypes
void init_DAC();                 // initialize DAC
void out_sample(sample* outDAC); // output sample to DAC

#endif
