#include "modules.h"

// -> GENERIC
// this will be the generic format for each module struct
// to be used as a place holder for compiler when calling arbitrary modules 

// -> DELAY LINE
void proc_delay_line(delay_line self, param paramDelay) {
  unsigned int toDelay = map(paramDelay, 0, 255, 800, self->len);
  *(self->buffPos) = *(self->input);
  *(self->output) = access_buffer(self->buffHead, self->buffPos, self->len, toDelay);
  self->buffPos = adv_buffer(self->buffHead, self->buffPos, self->len);
}

delay_line new_delay_line(sample* in, sample* out, unsigned int maxLen) {
  // allocate the memory for this delay line object
  delay_line self = (delay_line) malloc(sizeof(struct delay_line_struct));
  // set the input and output pointers
  self->input = in;
  self->output = out;
  // allocate memory for buffer
  self->len = maxLen;
  self->buffHead = init_buffer(maxLen);
  self->buffPos = self->buffHead;
  // set the function pointers
  self->proc = &proc_delay_line;
  // return pointer to newly instantiated object
  return self;
}

// -> GAIN
void proc_gain(gain self, param paramGain) {
  if (self->linlog == LINEAR)
    *(self->output) = *(self->input)*self->maxGain*linearLUT[paramGain];
  if (self->linlog == LOG)
    *(self->output) = *(self->input)*self->maxGain*logLUT[paramGain];
}

gain new_gain(sample* in, sample* out, unsigned short maxGain, bool type) {
  // allocate the memory for this delay line object
  gain self = (gain) malloc(sizeof(struct gain_struct));
  // set the input and output pointers
  self->input = in;
  self->output = out;
  // set data
  self->maxGain = maxGain;
  self->linlog = type;
  // set the function pointers
  self->proc = &proc_gain;
  // return pointer to newly instantiated object
  return self;
}

// -> SUMMER
void proc_summer(summer self) {
  *(self->output) = *(self->inputOne) + *(self->inputTwo);
}

summer new_summer(sample* inOne, sample* inTwo, sample* out) {
  // allocate memory for this summer object
  summer self = (summer) malloc(sizeof(struct summer_struct));
  // set the input and output pointers
  self->inputOne = inOne;
  self->inputTwo = inTwo;
  self->output = out;
  // set the functions pointers
  self->proc = &proc_summer;
  // return pointer to newly instantiated object
  return self;
}
