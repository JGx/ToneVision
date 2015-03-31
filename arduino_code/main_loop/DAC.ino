#include "DAC.h"

// code sourced from:
// http://www.electrosmash.com/pedalshield
// with modifications by CL

void init_DAC() {
  // DAC Configuration
  analogWrite(OUT_DAC_POS,0);  // Enables DAC0
  analogWrite(OUT_DAC_NEG,0);  // Enables DAC1
}

void out_sample(sample* outDAC) {
  // Write the DACs
  dacc_set_channel_selection(DACC_INTERFACE, 0);                    //select DAC channel 0
  dacc_write_conversion_data(DACC_INTERFACE, (*outDAC>>1)+2048);    //write on DAC TODO - add differential output
  dacc_set_channel_selection(DACC_INTERFACE, 1);                    //select DAC channel 1
  dacc_write_conversion_data(DACC_INTERFACE, (-(*outDAC>>1))+2048); //write on DAC TODO - add differential output
}
