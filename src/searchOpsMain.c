/*
Version No:
*/

#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"
#include "searchOpsMain.h"
#include "searchOps.h"

int main(int argc,char *argv[]){

    FILE *bloomFp = NULL;
    
    char *cPtr_bloomFilter = NULL;
    char *cPtr_pattern = NULL; 
    int i_retVal = FAILURE;
    
    if(argc != 2){
         return (1);
    } 
         
    if( (bloomFp = fopen(argv[1],"r")) == NULL){

    }

    /* Load the bloom filter into the main memory */
    cPtr_bloomFilter = cPtr_loadBloomFilter(bloomFp);

    if( NULL != cPtr_bloomFilter){

         do{
              /* Get the patterns from the text file in which the patterns
                 will be stored.
              */
              cPtr_pattern = cPtr_getPatternFromFile();
              
              /* Search the pattern in the bloom filter */
              i_retVal = i_performSearchOperation(cPtr_bloomFilter,cPtr_pattern);

              if(SUCCESS == i_retVal){
                   /* Write it into a file */
                   v_writePatternToFile(cPtr_pattern);
              }

         } while(NULL != cPtr_pattern);
         
    }
    return 0;
}
