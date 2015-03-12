#ifndef ADC_H
#define ADC_H

#include "defines.h"

// analog inputs 
#define IN_ADC_CH 7 // ADC channel for A0 
#define ADC_CH_MASK 0x03CC0
#define NUM_KNOBS 4

// globals
param knobList[NUM_KNOBS]; // array of pointers to knob vals

// function prototypes
void init_ADC();                // initialize ADC
void get_sample(sample* inPos); // get input from two ADCs, add signal together
void read_knobs(void);          // read all parameter knobs

#endif
