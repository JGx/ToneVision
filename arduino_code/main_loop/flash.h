#ifndef FLASH_H
#define FLASH_H

#include "defines.h"
#include "DueFlashStorage.h"

// defines
#define MEM_START 0 // address of first element of list recieved from web

// globals
DueFlashStorage dueFlashStorage;

// function prototypes
void writeInt(int address, int* toWritePtr);   // write an integer to flash
int* readInt(int address);                     // read an integer from flash 
void writeIntArray(int address, int* toWrite); // write an integer array to flash
int* readIntArray(int address);                // read an integer array from flash, return same array in RAM

#endif
