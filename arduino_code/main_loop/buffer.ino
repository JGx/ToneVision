#include "buffer.h"

// creates buffer, initializes it to 0
sample* init_buffer(unsigned int len) {
  sample* buff; 
  buff = (sample*) malloc(len*SIZE_OF_SAMPLE);
  
  if(buff) {
    // initialize all vals to 0
    unsigned short i;
    for(i=0; i<len; i++) {
      buff[i] = 0;
    }
    // return pointer to first element
    return buff;
  } else {
    return NULL;
  }
}

// advances pointer to next index and wraps pointer if necessary
// TODO switch to using modulus
sample* adv_buffer(sample* head, sample* inPos, unsigned int len) {
  if((inPos-head) >= (len-1)) {
    return inPos+1-len;
  } else {
    return inPos+1;
  }
}

// returns value from the buffer offset by a number of samples
sample access_buffer(sample* head, sample* currPos, unsigned int len, unsigned int offset) {
    return *(head + (int)(currPos-head + offset)%len);
}

