#include "modules.h"

// -> GENERIC
// generic "new" function for all types of modules
// "list" is an array of all the data that needs to be set in the struct
generic new_generic(id modID, int* list) {
  switch(modID) {
    case DELAY_ID:
      return new_delay_line((sample*) list[0], (sample*) list[1], (unsigned int) list[2]);
      break;
    case GAIN_ID:
      return new_gain((sample*) list[0], (sample*) list[1], (unsigned short) list[2], (bool) list[3]);
      break;
    case SUMMER_ID:
      return new_summer((sample*) list[0], (sample*) list[1], (sample*) list[2]);
      break;
    default:
      return NULL;
      break;
  }
}

// -> DELAY LINE
void proc_delay_line(delay_line self, param paramDelay) {
  unsigned int toDelay = map(paramDelay, 0, 255, 1500, self->len);
  *(self->buffPos) = 0;
  *(self->buffPos) = *(self->input);
  *(self->output) = access_buffer(self->buffHead, self->buffPos, self->len, toDelay);
  self->buffPos = adv_buffer(self->buffHead, self->buffPos, self->len);
}

generic new_delay_line(sample* in, sample* out, unsigned int maxLen) {
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
  return (generic) self;
}

// -> GAIN
void proc_gain(gain self, param paramGain) {
  if (self->linlog == LINEAR)
    *(self->output) = *(self->input)*self->maxGain*linearLUT[paramGain];
  if (self->linlog == LOG)
    *(self->output) = *(self->input)*self->maxGain*logLUT[paramGain];
}

generic new_gain(sample* in, sample* out, unsigned short maxGain, bool type) {
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
  return (generic) self;
}

// -> SUMMER
void proc_summer(summer self) {
  sample sum = *(self->inputOne) + *(self->inputTwo);
  if (sum > 2048) {
    *(self->output) = 2048;
  } else if (sum < -2048) {
    *(self->output) = -2048;
  } else {
    *(self->output) = sum;
  }
}

generic new_summer(sample* inOne, sample* inTwo, sample* out) {
  // allocate memory for this summer object
  summer self = (summer) malloc(sizeof(struct summer_struct));
  // set the input and output pointers
  self->inputOne = inOne;
  self->inputTwo = inTwo;
  self->output = out;
  // set the functions pointers
  self->proc = &proc_summer;
  // return pointer to newly instantiated object
  return (generic) self;
}
