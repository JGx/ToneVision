#ifndef DAC_H
#define DAC_H
  
#include "defines.h"
  
// analog outputs
#define OUT_DAC_POS DAC0
#define OUT_DAC_NEG DAC1

// functions prototypes
void init_DAC(void);             // initialize DAC
void out_sample(sample* outDAC); // output sample to DAC

#endif
