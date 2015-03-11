#include "flash.h"

void writeInt(int address, int* toWritePtr) {
  dueFlashStorage.write(address,(byte*)toWritePtr,sizeof(int));
}

int* readInt(int address) {
  return (int*)dueFlashStorage.readAddress(address);
}

void writeIntArray(int address, int* toWrite) {
  int num = toWrite[0]; // get number of elements
  
  for(int i=0; i<num; i++) {
    writeInt(address+i*sizeof(int),&toWrite[i]);
  }
}

int* readIntArray(int address) {
  int num = *readInt(address);                 // get number of elements
  Serial.print("num: ");
  Serial.println(num);
  if(num <= 0) {                               // check for valid number of elements
    return NULL;
  }
  int* list = (int*) malloc(num*sizeof(int));  // allocate memory for list to return
  
  Serial.println("int readIntArray");
  for(int i=0; i<num; i++) {
    list[i] = *readInt(address+i*sizeof(int)); // read out values from flash
    Serial.println(list[i]);
  }
  
  return list;
}
