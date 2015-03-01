#include "DAC.h"

// code sourced from:
// http://www.electrosmash.com/pedalshield
// with modifications by CL

void init_DAC() {
  // DAC Configuration
  analogWrite(OUT_DAC,0);  // Enables DAC0
}

void out_sample(sample* outDAC) {
  // Write the DACs
  dacc_set_channel_selection(DACC_INTERFACE, 1);              //select DAC channel 1
  dacc_write_conversion_data(DACC_INTERFACE, *outDAC + 2048); //write on DAC
}
