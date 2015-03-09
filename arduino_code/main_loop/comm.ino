#include "comm.h"

sample** inst_nets(int num) {
  // create array of pointers to samples
  sample** ptrArry = (sample**) malloc(num*sizeof(sample*));
  // instantiate each sample
  for(int i=0; i<num; i++) {
    ptrArry[i] = (sample*) malloc(sizeof(sample));
  }
  // initialize each sample to 0
  for(int i=0; i<num; i++) {
    *(ptrArry[i]) = 0;
  }
  // return pointer to head of array
  return ptrArry;
}

void get_serial_data() {
  // get number of modules
  const int debugNumMods = 5;
  numMods = debugNumMods;
  
  // instantiate modID array 
  modIDList = (int*) malloc(numMods*sizeof(int));
  
  int debugIDList[debugNumMods] = {DELAY_ID,SUMMER_ID,SUMMER_ID,GAIN_ID,GAIN_ID};
  // populate ID list
  for(int i=0; i<numMods; i++) {
    modIDList[i] = debugIDList[i];
  }
  
  // get number of nets
  const int debugNumNets = 6;
  numNets = debugNumNets;
  
  // instantiate input array 
  inList = (int*) malloc(numMods*sizeof(int));
  
  int debugInList[debugNumMods] = {3,0,4,4,0};
  // populate module input list
  for(int i=0; i<numMods; i++) {
    inList[i] = debugInList[i];
  }
  
  // instantiate output array 
  outList = (int*) malloc(numMods*sizeof(int));
  
  int debugOutList[debugNumMods] = {4,3,1,2,5};
  // populate module output list
  for(int i=0; i<numMods; i++) {
    outList[i] = debugOutList[i];
  }
  
  // get number of args
  const int debugNumArgs = 7;
  numArgs = debugNumArgs;
  
  // instantiate arg array 
  argList = (int*) malloc(numArgs*sizeof(int));
  
  int debugArgList[debugNumArgs] = {15000,2,5,1,LINEAR,1,LINEAR};
  // populate argument list
  for(int i=0; i<numArgs; i++) {
    argList[i] = debugArgList[i];
  }

  // generate parsed list
  parsedArgList = parse_args(numMods, argList, modIDList);
}

int** parse_args(int num, int* list, int* IDlist) {
  int** parsed_list;                              // instantiate parsed list of args
  parsed_list = (int**) malloc(num*sizeof(int*)); // allocate memory for array of args (one index for each module)
  int currListIndex = 0;                          // keeps track of index in big list
  Serial.println("in parse args");
  Serial.println("listing IDs");
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
