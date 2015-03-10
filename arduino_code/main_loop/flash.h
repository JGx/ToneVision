#ifndef FLASH_H
#define FLASH_H

#include "defines.h"
#include "DueFlashStorage.h"

// globals
DueFlashStorage dueFlashStorage;

// function prototypes
void writeInt(int address, int* toWritePtr);
int* readInt(int address);

#endif
