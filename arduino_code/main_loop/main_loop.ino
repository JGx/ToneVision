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
delay_line delay1;
gain gain1;
summer summer1;

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
  
  // initialize modules
  delay1 = new_delay_line(summerOutPtr, currOutSamplePtr, 15000);
  gain1 = new_gain(currOutSamplePtr, feedbackOutPtr, 1, LINEAR);
  summer1 = new_summer(currInSamplePtr, feedbackOutPtr, summerOutPtr);
  
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
  summer1->proc(summer1);
  delay1->proc(delay1, knob0);
  gain1->proc(gain1, knob1);
  // throughput
//  *(currOutSamplePtr) = *(currInSamplePtr);
  
  // output sample to DAC
  out_sample(currOutSamplePtr);
}
