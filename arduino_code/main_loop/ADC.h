#ifndef ADC_H
#define ADC_H

#include "defines.h"

// analog inputs 
#define IN_ADC_CH 7 // ADC channel for A0 positive part of wave 
#define ADC_CH_MASK 0x02CC0

// globals
uint8 knob0;
uint8 knob1;
uint8 knob2;
uint8 knob3;

// function prototypes
void init_ADC();                // initialize ADC
void get_sample(sample* inPos); // get input from two ADCs, add signal together
void read_knobs();              // read all parameter knobs

#endif
