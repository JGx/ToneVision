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
  const int debugNumMods = 3;
  numMods = debugNumMods;
  
  // instantiate modID array 
  modIDList = (int*) malloc(numMods*sizeof(int));
  
  int debugIDList[debugNumMods] = {0,1,2};
  // populate ID list
  Serial.println("in populate ID List");
  for(int i=0; i<numMods; i++) {
    modIDList[i] = debugIDList[i];
    Serial.println(modIDList[i]);
  }
  
  // get number of nets
  const int debugNumNets = 4;
  numNets = debugNumNets;
  
  // instantiate input array 
  inList = (int*) malloc(numMods*sizeof(int));
  
  int debugInList[debugNumMods] = {2,1,0};
  // populate module input list
  Serial.println("in populate input List");
  for(int i=0; i<numMods; i++) {
    inList[i] = debugInList[i];
    Serial.println(inList[i]);
  }
  
  // instantiate output array 
  outList = (int*) malloc(numMods*sizeof(int));
  
  int debugOutList[debugNumMods] = {1,3,2};
  // populate module output list
  Serial.println("in populate output List");
  for(int i=0; i<numMods; i++) {
    outList[i] = debugOutList[i];
    Serial.println(outList[i]);
  }
  
  // get number of args
  const int debugNumArgs = 4;
  numArgs = debugNumArgs;
  
  // instantiate arg array 
  argList = (int*) malloc(numArgs*sizeof(int));
  
  int debugArgList[debugNumArgs] = {15000,1,LINEAR,3};
  // populate argument list
  Serial.println("printing argList");
  for(int i=0; i<numArgs; i++) {
    argList[i] = debugArgList[i];
    Serial.print(argList[i]);
    Serial.print(" ");
  }
  Serial.println();
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
    Serial.print("currListIndex: ");
    Serial.println(currListIndex);
    Serial.print("i: ");
    Serial.println(i);
    int currID = modIDList[i];     // current module ID we are looking at
    Serial.print("modIDList[i]: ");
    Serial.println(modIDList[i]);  // TODO - this is getting frigged up, modIDList doesnt match what its initiated to
    int currNumParams = NUMARGSLIST[currID];      // number of parameters for module we are looking at 
    parsed_list[i] = (int*) malloc(currNumParams*sizeof(int)); // allocate memory for each row (parameter list for each module)
    
    // for each module, populate a row of parameters from master arg list
    for(int j=0; j<currNumParams; j++) {
      Serial.print("j: ");
      Serial.println(j);
      *(parsed_list[i]+j) = argList[currListIndex+j];
      int temp = *(parsed_list[i]+j);
      Serial.print("*(parsed_list[i]+j)");
      Serial.println(temp);
    }
    Serial.println();
    // update list index
    currListIndex = currListIndex + currNumParams;
  }
}
