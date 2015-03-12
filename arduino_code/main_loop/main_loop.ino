// ToneVision Project
// main loop
//
// by: Cooper Loughlin

// includes
#include "defines.h"
#include "ADC.h"
#include "timer.h"
#include "DAC.h"
#include "modules.h"
#include "buffer.h"
#include "comm.h"
#include "flash.h"
#include "DueFlashStorage.h"

// various debug
#define LED_OB 13 // on board LED
unsigned short LEDState;

void setup() {
  // stop interrupts
  noInterrupts();
  
  // default to false
  fatalError = false;
  
  // various debug
  LEDState = 0;
  pinMode(LED_OB, OUTPUT);
  digitalWrite(LED_OB, LOW);
  
  // turn serial on
  Serial.begin(9600);
  
  // get serial data
//  int* debugArray = (int*) debugArrayConst;
  int* prevList = readIntArray(MEM_START); // pull list from flash (from previous power cycle)
  parse_serial_data(prevList);

  // set default values for currIn/OutSamplePtr
  currInSamplePtr = (sample*)malloc(sizeof(sample));
  currOutSamplePtr = (sample*)malloc(sizeof(sample));

  // check for fatal error
  // if no fatal error, go to effect defined by list in flash memory 
  if(!fatalError) { 
    // instantiate signals
    netList = inst_nets();
    currInSamplePtr = netList[0];  // always set input to first member of netlist
    currOutSamplePtr = netList[1]; // always set output to second member of netlist
    
    // instantiate modules
    inst_modules();
  }
  
  // init functions
  init_timer(); 
  init_ADC();
  init_DAC();
  
  // allow interrupts
  interrupts();
}

void loop() {
  read_knobs();
  check_comm();
}

// interrupt handler for samples
// all ADC, processing, and DAC code goes in this function
void TC4_Handler()
{
  // We need to get the status to clear it and allow the interrupt to fire again
  TC_GetStatus(TC1, 1);
  
  // get values from ADCs
  get_sample(currInSamplePtr);
  
  // do processing here
  if(fatalError) { // if fatal error, default to throughput
    // throughput
    *(currOutSamplePtr) = *(currInSamplePtr);
  } else {
//    modList[0]->proc(modList[0], knob0);
//    modList[1]->proc(modList[1], NULL);
//    modList[2]->proc(modList[2], NULL);
//    modList[3]->proc(modList[3], knob1);
//    modList[4]->proc(modList[4], knob2);
  }
  
  // output sample to DAC
  out_sample(currOutSamplePtr);
}
