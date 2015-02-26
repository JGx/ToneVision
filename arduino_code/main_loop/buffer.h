#ifndef BUFFER_H
#define BUFFER_H

#include "defines.h"

// function prototypes
sample* init_buffer(unsigned int len);
sample* adv_buffer(sample* head, sample* inPos, unsigned int len);
sample access_buffer(sample* head, sample* currPos, unsigned int len, unsigned int offset);

#endif
