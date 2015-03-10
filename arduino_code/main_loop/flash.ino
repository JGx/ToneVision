#include "flash.h"

void writeInt(int address, int* toWritePtr) {
  dueFlashStorage.write(address,(byte*)toWritePtr,sizeof(int));
}

int* readInt(int address) {
  return (int*)dueFlashStorage.readAddress(address);
}
