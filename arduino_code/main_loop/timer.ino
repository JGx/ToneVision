#include "timer.h"

// set up ineterrupt at 44.1 kHz
// code sourced from:
// http://rcarduino.blogspot.co.uk/2012/12/arduino-due-dds-part-1-sinewaves-and.html
// with modifications by CL
void init_timer() {
  /* turn on the timer clock in the power management controller */
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC4);

  /* we want wavesel 01 with RC */
  TC_Configure(/* clock */TC1,/* channel */1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK2);
  TC_SetRC(TC1, 1, 238); // sets <> 44.1 Khz interrupt rate
  TC_Start(TC1, 1);
  
  enable_TC();
  
  /* Enable the interrupt in the nested vector interrupt controller */
  /* TC4_IRQn where 4 is the timer number * timer channels (3) + the channel number (=(1*3)+1) for timer1 channel1 */
  NVIC_EnableIRQ(TC4_IRQn);
}

void enable_TC() {
  // enable timer interrupts on the timer 
  TC1->TC_CHANNEL[1].TC_IER=CPCS_MASK;
  TC1->TC_CHANNEL[1].TC_IDR=~CPCS_MASK;
}

void disable_TC() {
  // enable timer interrupts on the timer 
  TC1->TC_CHANNEL[1].TC_IER=~CPCS_MASK;
  TC1->TC_CHANNEL[1].TC_IDR=CPCS_MASK;
}
