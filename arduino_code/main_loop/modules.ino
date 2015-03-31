#include "modules.h"

void inst_modules() {
  // instantiate module list 
  modList = (generic*) malloc(numMods*sizeof(generic));
  
  // instantiate each module
  for(int i=0; i<numMods; i++) {
    modList[i] = new_generic(modIDList[i], netList[inList[i]], netList[outList[i]], parsedArgList[i]);
  }
}

// **********************
// * PROCESSING MODULES *
// **********************

// -> GENERIC
// generic "new" function for all types of modules
// "list" is an array of all the data that needs to be set in the struct
generic new_generic(id modID, sample* in, sample* out, int* list) {
  switch(modID) {
    case DELAY_ID:
      return new_delay_line(in, out, (unsigned int) list[0], (unsigned int) list[1]);
      break;
    case GAIN_ID:
      return new_gain(in, out, (unsigned short) list[0], (bool) list[1]);
      break;
    case SUMMER_ID:
      return new_summer(in, out, list[0]);
      break;
    case ENV_ID: // TODO write this line
      return new_env(in, (param*) out);
      break;
    default:
      return NULL;
      break;
  }
}

// -> DELAY LINE
void proc_delay_line(delay_line self, param* paramDelay) {
  unsigned int toDelay = map(*paramDelay, 0, 255, self->minDelay, self->len);
  *(self->buffPos) = 0;
  *(self->buffPos) = *(self->input);
  *(self->output) = access_buffer(self->buffHead, self->buffPos, self->len, toDelay);
  self->buffPos = adv_buffer(self->buffHead, self->buffPos, self->len);
}

generic new_delay_line(sample* in, sample* out, unsigned int minLen, unsigned int maxLen) {
  // allocate the memory for this delay line object
  delay_line self = (delay_line) malloc(sizeof(struct delay_line_struct));
  // set the input and output pointers
  self->input = in;
  self->output = out;
  // allocate memory for buffer
  self->minDelay = minLen;
  self->len = maxLen;
  self->buffHead = init_buffer(maxLen);
  self->buffPos = self->buffHead;
  // set the function pointers
  self->proc = &proc_delay_line;
  // return pointer to newly instantiated object
  return (generic) self;
}

// -> GAIN
void proc_gain(gain self, param* paramGain) {
  if (self->linlog == LINEAR)
    *(self->output) = *(self->input)*self->maxGain*linearLUT[*paramGain];
  if (self->linlog == LOG)
    *(self->output) = *(self->input)*self->maxGain*logLUT[*paramGain];
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

generic new_summer(sample* inOne, sample* out, int inTwoIndex) {
  // allocate memory for this summer object
  summer self = (summer) malloc(sizeof(struct summer_struct));
  // set the input and output pointers
  self->inputOne = inOne;
  self->inputTwo = netList[inTwoIndex];
  self->output = out;
  // set the functions pointers
  self->proc = &proc_summer;
  // return pointer to newly instantiated object
  return (generic) self;
}

// -> ENVELOPE DETECTOR
void proc_env(env self) {
  *(self->buffPos) = 0;
//  *(self->buffPos) = *(self->input);
  // previous output value from buffer
  sample prevOut = access_buffer(self->buffHead, self->buffPos, ENV_BUFF_LEN, 1);
  // check if input higher than prev buff pos
  if (*(self->input) > prevOut) {
    // charging
    *(self->buffPos) = prevOut + (sample) CHARGE_CONST*( (float) (*(self->input)) );
  } else {
    // discharging
    *(self->buffPos) = prevOut - (sample) DISCH_CONST*( (float) prevOut );
  }
  *(self->output) = *(self->buffPos);
  self->buffPos = adv_buffer(self->buffHead, self->buffPos, ENV_BUFF_LEN);
}

generic new_env(sample* in, param* out) {
  // allocate memory for this env object
  env self = (env) malloc(sizeof(struct env_struct));
  // set the input and output pointers
  self->input = in;
  self->output = out;
  self->buffHead = init_buffer(ENV_BUFF_LEN);
  self->buffPos = self->buffHead;
  // set the function pointer
  self->proc = &proc_env;
  // return pointer to newly instantiated object
  return (generic) self;
}
