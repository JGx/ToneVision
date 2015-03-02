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

int** parse_params(int num, int* list, int* IDlist) {
  int** parsed_list;                              // instantiate parsed list of parameters
  parsed_list = (int**) malloc(num*sizeof(int*)); // allocate memory for array of parameters (one for each module)
  int currListIndex = 0;                          // keeps track of index in big list
  for(int i=0; i<num; i++) {
    int currID = IDlist[i];                  // current module ID we are looking at
    int currNumParams = NUMARGSLIST[currID]; // number of parameters for module we are looking at 
    parsed_list[i] = (int*) malloc(currNumParams*sizeof(int)); // allocate memory for each row (parameter list for each module)
    
    // for each module, populate a row of parameters
    for(int j=0; j<currNumParams; j++) {
      parsed_list[i][j] = currListIndex+j;
    }
    
    // update list index
    currListIndex = currListIndex + currNumParams;
  }
}
