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
    case ENV_ID: 
      return new_env(in, (param*) out);
      break;
    case FILTER_ID: 
      return new_filter(in, out);
      break;
    default:
      return NULL;
      break;
  }
}

// -> DELAY LINE
void proc_delay_line(delay_line self, param* paramDelay) {
  param newParam = (*paramDelay)<<5; // to get smooth changes when adjusting param
  self->prevParam = (param)((float)(newParam - self->prevParam)*DELAY_K) + self->prevParam;
//  Serial.println(self->prevParam);
  unsigned int toDelay = map(self->prevParam, 0, 8191, self->minDelay, self->len);
//  Serial.println(toDelay);
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
  self->prevParam = 0;
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
  if (sum > 4096) {
    *(self->output) = 4096;
  } else if (sum < -4096) {
    *(self->output) = -4096;
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
  self->currIn = (float) abs(*(self->input)); // rectify input signal

  self->prevOut = (self->currIn - self->prevOut)*((float) ENV_K) + self->prevOut;
  *(self->output) = ((sample) self->prevOut)>>4;  // shift by 4 to get in range of params
}

generic new_env(sample* in, param* out) {
  // allocate memory for this env object
  env self = (env) malloc(sizeof(struct env_struct));
  // set the input and output pointers
  self->input = in;
  self->output = out;
  self->currIn = 0;
  self->prevOut = 0;
  // set the function pointer
  self->proc = &proc_env;
  // return pointer to newly instantiated object
  return (generic) self;
}

// -> FILTER
void proc_filter(filter self, param* cutoff) {
  self->currIn = (int) (*self->input);
  self->currOut = (lowPassLUT[*cutoff][0]*self->currIn)/FILT_DIV + (lowPassLUT[*cutoff][1]*self->inBuff1)/FILT_DIV 
                                + (lowPassLUT[*cutoff][2]*self->inBuff2)/FILT_DIV
                                + (lowPassLUT[*cutoff][3]*self->outBuff0)/FILT_DIV
                                + (lowPassLUT[*cutoff][4]*self->outBuff1)/FILT_DIV;
  
  // update buffers
  self->inBuff2 = self->inBuff1;
  self->inBuff1 = self->currIn;
  self->outBuff1 = self->outBuff0;
  self->outBuff0 = self->currOut;
  
  // set output
  (*self->output) = (sample) self->currOut;
}

generic new_filter(sample* in, sample* out) {
  // allocate memory for this env object
  filter self = (filter) malloc(sizeof(struct filter_struct));
  // set the input and output pointers
  self->input = in;
  self->output = out;
  // initialize buffers
  self->currIn = 0;
  self->currOut = 0;
  self->inBuff1 = 0;
  self->inBuff2 = 0;
  self->outBuff0 = 0;
  self->outBuff1 = 0;
  // set the function pointer
  self->proc = &proc_filter;
  // return pointer to newly instantiated object
  return (generic) self;
}
