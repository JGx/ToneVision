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
  // if no list, jump out of function
  if(list == NULL) {  
    Serial.println("list pointer is NULL");
    fatalError = true;
    return;
  }
    
  int currListIndex; // keeps track index in list from web app
  currListIndex = 1; // 0 = total number elements, 1 = numMods
  
  // get number of modules
  numMods = list[currListIndex]; // second element will always be numMods (first element is total number of elements in li
  currListIndex++;               // increment currListIndex
  // instantiate modID array 
  modIDList = parse_main_list(list, numMods, &currListIndex);
  
  // get number of nets
  numNets = list[currListIndex];
  currListIndex++;
  
  // instantiate input array 
  inList = parse_main_list(list, numMods, &currListIndex);
  // instantiate output array 
  outList = parse_main_list(list, numMods, &currListIndex);
    
  // get number of args
  numArgs = list[currListIndex];
  currListIndex++;
  
  // instantiate arg array 
  argList = parse_main_list(list, numArgs, &currListIndex);
  // generate parsed list
  parsedArgList = parse_args(numMods, argList, modIDList);
  
  // instantiate paramID array
  paramIDList = parse_main_list(list, numMods, &currListIndex);
  // instantiate param array
  paramList = parse_main_list(list, numMods, &currListIndex);
  // generate instantied param pointer list
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
  int* listToReturn = (int*) malloc(num*sizeof(int));
  
  for(int i=0; i<num; i++) {
    listToReturn[i] = list[(*currIndexPtr)+i];
  }
  
  (*currIndexPtr) = (*currIndexPtr)+num; // update list index
  
  return listToReturn;
}

param** create_param_ptrs(void) {
  // instantiate array 
  param** toReturn = (param**) malloc(numMods*sizeof(param*));

  // iterate through list of params, deal with each modules param
  for(int i=0; i<numMods; i++) {
    // look at each modules param type ID
    switch(paramIDList[i]) {
      case PARAM_STATIC_ID:
        toReturn[i] = (param*) malloc(sizeof(param));
        (*toReturn[i]) = paramList[i];
        break;
      case PARAM_NET_ID:
        toReturn[i] = (param*) netList[paramList[i]];
        break;
      case PARAM_KNOB_ID:
        toReturn[i] = (param*) &knobList[paramList[i]];
        break;
      case PARAM_NONE_ID:
        toReturn[i] = NULL;
        break;
      default:
        toReturn[i] = NULL;
        break;
    }
  }
  return toReturn;
}
