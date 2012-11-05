#include "searchOps.h"
#include "hashFunctions.h"

/*
Function Name:
Description:
Parameters;
Return Type:
*/
int i_performSearchOperation(char *cPtr_bloomFilter,char *cPtr_pattern){

    int i = 0;
    int i_retVal = -1;
    unsigned long ul_searchIndex[NUM_HASH_FUNCTIONS];
    unsigned int ui_frequencyArr[NUM_HASH_FUNCTIONS];

    ul_searchIndex[i++] = hashFunctionOne(cPtr_pattern,0);
    /*
    ul_searchIndex[i++] = hashFunctionTwo(cPtr_pattern,0);
    ul_searchIndex[i++] = hashFunctionThree(cPtr_pattern,0);
    ul_searchIndex[i++] = hashFunctionFour(cPtr_pattern,0);
    */
    i_retVal = i_getFrequency(ul_searchIndex,ui_frequencyArr);    

    for(i = 0; i < NUM_HASH_FUNCTIONS; i++){
         if(ui_frequencyArr[i] < FREQUENCY){
              return FAILURE;
         }
    }

    /* Remove these stmts later */
    i_retVal++;
    ul_searchIndex[0] = 10;
    ui_frequencyArr[0] = 10;

    return SUCCESS;
}


/*
Function Name:
Description:
Parameters;
Return Type:
*/
int i_getFrequency(unsigned long *ulPtr_searchIndex,unsigned int *uiPtr_frequencyArr){

    return SUCCESS;
}
