#include "comm.h"

sample** inst_nets(void) {
  // create array of pointers to samples
  sample** ptrArry = (sample**) malloc(numNets*sizeof(sample*));
  // instantiate each sample
  for(int i=0; i<numNets; i++) {
    ptrArry[i] = (sample*) malloc(sizeof(sample));
  }
  // initialize each sample to 0
  for(int i=0; i<numNets; i++) {
    *(ptrArry[i]) = 0;
  }
  // return pointer to head of array
  return ptrArry;
}

void parse_serial_data(int* list) {
  
  if(list == NULL) {  // if no list, jump out of function
    Serial.println("list pointer is NULL");
    fatalError = true;
    return;
  }
    
  int currListIndex; // keeps track index in list from web app
  currListIndex = 1; // 0 = total number elements, 1 = numMods
  
  // get number of modules
  numMods = list[currListIndex]; // second element will always be numMods (first element is total number of elements in li
  currListIndex++;               // increment currListIndex

  // TODO write helper function for all this shit
  // instantiate modID array 
  modIDList = (int*) malloc(numMods*sizeof(int));
  
  // populate ID list
  for(int i=0; i<numMods; i++) {
    modIDList[i] = list[currListIndex+i]; // get mod IDs from big list
  }
  
  currListIndex = currListIndex+numMods; // keep track of list index
  
  // get number of nets
  numNets = list[currListIndex];
  currListIndex++;
  
  // instantiate input array 
  inList = (int*) malloc(numMods*sizeof(int));
  
  // populate module input list
  for(int i=0; i<numMods; i++) {
    inList[i] = list[currListIndex+i];
  }

  currListIndex = currListIndex+numMods; // keep track of list index
  
  // instantiate output array 
  outList = (int*) malloc(numMods*sizeof(int));
  
  // populate module output list
  for(int i=0; i<numMods; i++) {
    outList[i] = list[currListIndex+i];
  }
  
  currListIndex = currListIndex+numMods; // keep track of list index
  
  // get number of args
  numArgs = list[currListIndex];
  currListIndex++;
  
  // instantiate arg array 
  argList = (int*) malloc(numArgs*sizeof(int));
  
  // populate argument list
  for(int i=0; i<numArgs; i++) {
    argList[i] = list[currListIndex+i];
  }

  // generate parsed list
  parsedArgList = parse_args(numMods, argList, modIDList);
} 

void check_comm(void) {
  int* commList = NULL;            // list for storing data from serial
  
  if(Serial.available()) {
    disable_TC();                      // need to disable TC to make Serial.read() work
    commList = get_serial_data();      // acquire the serial data and store it in an array
    enable_TC();                       // re-enable timer interrupt
  }
  
  // print commList for debug
  if(commList != NULL) {
    writeIntArray(MEM_START,commList); // write list to flash memory
    int* flashList = readIntArray(MEM_START);
    for(int i=0; i<flashList[0]; i++) {
      Serial.println(flashList[i]);
    }
  }
}

int** parse_args(int num, int* list, int* IDlist) {
  int** parsed_list;                              // instantiate parsed list of args
  parsed_list = (int**) malloc(num*sizeof(int*)); // allocate memory for array of args (one index for each module)
  int currListIndex = 0;                          // keeps track of index in big list
  for(int i=0; i<num; i++) {
    int currID = modIDList[i];     // current module ID we are looking at
    int currNumParams = NUMARGSLIST[currID];      // number of parameters for module we are looking at 
    parsed_list[i] = (int*) malloc(currNumParams*sizeof(int)); // allocate memory for each row (parameter list for each module)
    
    // for each module, populate a row of parameters from master arg list
    for(int j=0; j<currNumParams; j++) {
      *(parsed_list[i]+j) = argList[currListIndex+j];
      int temp = *(parsed_list[i]+j);
    }
    // update list index
    currListIndex = currListIndex + currNumParams;
  }
  
  return parsed_list;
}

int* get_serial_data(void) {
  int numEl = Serial.parseInt();                // get total number of list elements (including this element)
  
  if(numEl <= 0) {                              // check that we have a valid number of elements
    return NULL;
  }
  
  int* list = (int*) malloc(numEl*sizeof(int)); // instantiate an array for list
  list[0] = numEl;                              // always set the first element equal number of elements
  
  for(int i=1; i<numEl; i++) {
    list[i] = Serial.parseInt();                // populate list
  }
  
  return list;                                  // return head of array
}

int* parse_main_list(int* list, int num, int* currIndexPtr) {
  
}

