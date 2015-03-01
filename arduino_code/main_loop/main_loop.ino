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

// various debug
#define LED_OB 13 // on board LED
unsigned short LEDState;

// instantiate modules
generic modList[3];

// instantiate signals
sample summerOut;
sample* summerOutPtr;
sample feedbackOut;
sample* feedbackOutPtr;

void setup() {
  // stop interrupts
  noInterrupts();
  
  // various debug
  LEDState = 0;
  pinMode(LED_OB, OUTPUT);
  digitalWrite(LED_OB, LOW);
  Serial.begin(9600);
  
  // init functions
  init_timer();
  init_ADC();
  init_DAC();
  
  // initialize signals
  summerOut = 0;
  feedbackOut = 0;
  summerOutPtr = &summerOut;
  feedbackOutPtr = &feedbackOut;
  
  int delayList[3] = {(int) summerOutPtr, (int) currOutSamplePtr, (int) 15000};
  int gainList[4] = {(int) currOutSamplePtr, (int) feedbackOutPtr, (int) 1, (int) LINEAR};
  int summerList[3] = {(int) currInSamplePtr, (int) feedbackOutPtr, (int) summerOutPtr};
  
  // initialize modules
  modList[0] = new_generic(DELAY_ID, delayList);
  modList[1] = new_generic(GAIN_ID, gainList);
  modList[2] = new_generic(SUMMER_ID, summerList);
  
  // allow interrupts
  interrupts();
}

void loop() {
  read_knobs();
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
  modList[0]->proc(modList[0], knob0);
  modList[1]->proc(modList[1], knob1);
  modList[2]->proc(modList[2], NULL);
  // throughput
//  *(currOutSamplePtr) = *(currInSamplePtr);
  
  // output sample to DAC
  out_sample(currOutSamplePtr);
}
