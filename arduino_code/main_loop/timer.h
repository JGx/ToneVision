#ifndef TIMER_H
#define TIMER_H

#include "defines.h"

// defines
#define CPCS_MASK 0x10

// function prototypes
void init_timer(void);
void enable_TC(void);
void disable_TC(void);
#endif
