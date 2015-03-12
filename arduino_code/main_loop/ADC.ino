#include "ADC.h"

void init_ADC() {
  // ADC Configuration
  // code sourced from:
  // http://www.electrosmash.com/pedalshield
  // with modifications by CL
  
  ADC->ADC_MR |= 0x80;        // DAC in free running mode.
  ADC->ADC_CR=2;              // Starts ADC conversion.
  ADC->ADC_CHER=ADC_CH_MASK;  // Enable ADC channels 0, 1, 10, 11, 12, 13. 
}

void get_sample(sample* inPos) {
  // this is faster than using analogWrite()
  // code sourced from:
  // http://www.electrosmash.com/pedalshield
  // with modifications by CL
  while((ADC->ADC_ISR & ADC_CH_MASK)!=ADC_CH_MASK); // wait for ADC 0, 1, 8, 9, 10, 11 conversion complete.
  *inPos = (sample) ADC->ADC_CDR[IN_ADC_CH] - 2048; // read data from ADC0, write to memory
                                                    // subtract 2048 to remove offset
}

void read_knobs() {
  float K = 0.1; // controller gain for knob reading LPF, got this value by experimenting
  // Read knobs
  while((ADC->ADC_ISR & ADC_CH_MASK)!=ADC_CH_MASK);  // wait for ADC 0, 1, 8, 9, 10, 11 conversion complete.
  knobList[0] = (param)((float)((int)((ADC->ADC_CDR[10])>>4) - knobList[0])*K + knobList[0]); // read data from ADC8        
  knobList[1] = (param)((float)((int)((ADC->ADC_CDR[11])>>4) - knobList[1])*K + knobList[1]); // read data from ADC9   
  knobList[2] = (param)((float)((int)((ADC->ADC_CDR[12])>>4) - knobList[2])*K + knobList[2]); // read data from ADC10 
  knobList[3] = (param)((float)((int)((ADC->ADC_CDR[13])>>4) - knobList[3])*K + knobList[3]); // read data from ADC11   
}
