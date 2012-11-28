#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "searchOps.h"
#include "hashFunctions.h"
#include "constants.h"

unsigned int ui_bloomFilter[BLOOMFILTERSIZE];
unsigned int ui_noOfPatterns;
/*
Function Name: ui_performSearchOps
Description: It gets all the patterns present in the pattern file and hashes 
             them into the Bloom-Filter, if the value at the hashed location is 
             >= the no.of.times the pattern must appear in the input string,then
             it marks such strings for writing them into a file which will be
             later used by KMP Algorithm to check if the pattern is actually 
             present those many no.of.times.
Parameters: void
Return Type: It returns the count of no.of.patterns that have been shortlisted
             for KMP Algorithm
*/
unsigned int ui_performSearchOps(){

    struct SearchPattern *headPtr = NULL;
    struct SearchPattern *temp = NULL;
   
    int flag = -1;

    /* Load the Bloom Filter */
    v_loadBloomFilter();

    ui_noOfPatterns = 0;

    headPtr = s_getPatternsFromFile();
#if SEARCH_DEBUG
    temp = headPtr;
    while(temp != NULL){
         printf("%s ",temp->c_pattern);
         printf("%u ",temp->ui_noOfTimes);
         printf("%d \n",temp->i_flag);
         temp = temp->nextPattern;
    }
#endif
    temp = headPtr;
    while(temp != NULL){
         flag = i_hashPattern(temp->c_pattern,temp->ui_noOfTimes,temp->i_flag);
         temp->i_flag = flag;
         temp = temp->nextPattern;
    }

    v_writeToFile(headPtr);

    return ui_noOfPatterns;
}

/*
Function Name: v_loadBloomFilter
Description: It loads the Bloom-Filter prepared by insert operation into the
             memory.
Parameters: void
Return Type: void
*/
void v_loadBloomFilter(){

    FILE *fpBloomFilter = NULL;

    int i = 0;

    if( (fpBloomFilter = fopen(BLOOMFILTERLOCATION,"r")) == NULL){
         printf("ERROR: Bloom-Filter file missing !\n");
         exit(1);
    }

    for(i = 0 ; i < BLOOMFILTERSIZE; i++){
         fscanf(fpBloomFilter,"%u ",&ui_bloomFilter[i]);
    }
    
    fclose(fpBloomFilter);
}

/*
Function Name: s_getPatternsFromFile
Description: It creates a linked list where each node in the list holds the 
             following information
Parameters:
Return Type:
*/
struct SearchPattern *s_getPatternsFromFile(){

    struct SearchPattern *headPtr = NULL;
    struct SearchPattern *tempPattern = NULL;
    FILE *fpPattern = NULL;

    if( (fpPattern = fopen(PATTERNFILELOCATION,"r")) == NULL){

    }

    while(!feof(fpPattern)){
         tempPattern = (struct SearchPattern *)malloc(sizeof(struct SearchPattern)*1);
         memset((void *)&(tempPattern->c_pattern),'\0',PATTERNLENGTH+1);
         fscanf(fpPattern,"%s %u \n",tempPattern->c_pattern,&tempPattern->ui_noOfTimes);
         tempPattern->c_pattern[PATTERNLENGTH] = '\0';
         tempPattern->i_flag = 0;
         tempPattern->nextPattern = headPtr;
         headPtr = tempPattern;
    }

    return headPtr;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
int i_hashPattern(char *cPtr_pattern,unsigned int ui_noOfTimes,int i_flag){

    unsigned int ui_hashIndex = 0;

    if( 0 == i_flag){
        ui_hashIndex = hashFunctionOne(cPtr_pattern,i_flag);
#if SEARCH_DEBUG
printf("DEBUG: BloomFilter Value is %d \n",ui_bloomFilter[ui_hashIndex]);
printf("DEBUG: Pattern must appear %u times \n",ui_noOfTimes);
#endif
         if( ui_bloomFilter[ui_hashIndex] < ui_noOfTimes ){
              return i_flag;
         } 
    } else if ( 0 == i_flag ){
         /*ui_hashIndex = hashFunctionTwo(cPtr_pattern,i_flag);*/
#if SEARCH_DEBUG
printf("DEBUG: BloomFilter Value is %d \n",ui_bloomFilter[ui_hashIndex]);
printf("DEBUG: Pattern must appear %u times \n",ui_noOfTimes);
#endif
        /* if( ui_bloomFilter[ui_hashIndex] < ui_noOfTimes ){
               return i_flag;
         }*/
    }

    /* Pattern is eligible for actual checking using KMP Algorithm */
    if( 0 == i_flag ){
         i_flag = 1;
    }
    
    return i_flag;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_writeToFile(struct SearchPattern *headPtr){

    struct SearchPattern *temp = NULL;
    FILE *fp = NULL;

    temp = headPtr;

    if( ( NULL != temp ) && ( NULL == fp ) ){

         if( (fp = fopen(ELIGIBLEPATTERNS,"w+")) == NULL ){

         }

         while(temp != NULL){
              if( 1 == temp->i_flag){
                   fprintf(fp,"%s %d \n",temp->c_pattern,temp->ui_noOfTimes);
                   ui_noOfPatterns++;
              } /* End of inner if */
              temp =  temp->nextPattern;
         } /* End of while */

         fclose(fp);

    } /* End of outer if */
    
}
