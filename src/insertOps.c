#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "insertOps.h"
#include "hashFunctions.h"
#include "inputString.h"
#include "patternString.h"
#include "global.h"

char c_buffer[BUFFERSIZE];
unsigned int ui_count = 0;
extern unsigned int ui_bloomFilter[BLOOMFILTERSIZE]; 
unsigned int klen_times=0;

/*
Function Name: i_performInsertOperation
Description: This function will populate the bloom filter using the input string
             which is stored in the file.
Parameters: void
Return Type: void
*/
int i_performInsertOperation(){

    char *cPtr_buffer = NULL;
    unsigned int ui_patternLength = 0;
    unsigned int ui_fileOffset = 0;
    
    time_t start_time,end_time;
    
    start_time= time(NULL);
    
    ui_patternLength = (unsigned int)i_getPatternLength();
         
    do{
         /* Read from the file where the input data string is stored and 
            populate into a buffer.
         */
         cPtr_buffer = cPtr_populateBuffer(ui_fileOffset);
 
         if( NULL != cPtr_buffer){
              /* Populate the Bloom Filter */
              ui_fileOffset = i_insertIntoBloomFilter(cPtr_buffer,ui_patternLength);
              exit(1);
         }

    } while (cPtr_buffer != NULL);
    end_time=time(NULL);
    printf("Exec time INSERT_BLOOM_FILTER: %f\n",difftime(end_time,start_time));
    printf("Number of strings of length %d generated : %d\n",ui_patternLength,klen_times);             
    /* Return the length of the pattern entered by the user */
    return ui_patternLength;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
char *cPtr_populateBuffer(unsigned int ui_offset){

    char *cPtr_buffer = NULL;

    FILE *inputFp = NULL;
    static unsigned int ui_filePtrOffset = 0;
   
    if( (inputFp = fopen(FILELOCATION,"r")) == NULL){
         printf("ERROR: Input file not found. \n");
         exit(1);
    } 

    /* Initialize the buffer to '\0' */
    memset(&c_buffer,'\0',BUFFERSIZE);
    cPtr_buffer = c_buffer;
    if( (fseek(inputFp,((BUFFERSIZE*ui_filePtrOffset)-ui_offset),SEEK_SET)) == -1){
         cPtr_buffer = NULL;
         return cPtr_buffer;
    }
    if(!feof(inputFp)){
         fread(cPtr_buffer,BUFFERSIZE,1,inputFp);
         ui_filePtrOffset++;
    }
    if( *cPtr_buffer == '\0'){
         cPtr_buffer = NULL;
         return cPtr_buffer;
    }
#if INS_DEBUG
    printf("Characters Read : %s \n",cPtr_buffer);
    printf("%d : No.of.characters %d \n",ui_filePtrOffset,strlen(cPtr_buffer));
#endif
    return cPtr_buffer;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
int i_insertIntoBloomFilter(char *cPtr_buffer,unsigned int ui_patternLength){

    char *cPtr_strLengthOfK = NULL;
    unsigned int ui_hashIndex = 0;
    int flag = 0;

    ui_count = 0;
    do{
         /* Read from buffer a string of length k */
         cPtr_strLengthOfK = cPtr_readStringOfLengthK(cPtr_buffer,ui_patternLength);
         
         if( NULL != cPtr_strLengthOfK){
              
              /* Perform hashing using hash function 01 */
              ui_hashIndex = hashFunctionOne(cPtr_strLengthOfK,flag);
#if INS_DEBUG
              printf(" Hash Index : %d \n",ui_hashIndex);
#endif
              v_updateBloomFilter(ui_hashIndex);

              /* Perform hashing using hash function 02 */
              ui_hashIndex = hashFunctionTwo(cPtr_strLengthOfK,flag);
#if INS_DEBUG
              printf(" Hash Index : %d \n",ui_hashIndex);
#endif
              v_updateBloomFilter(ui_hashIndex);
              if( 0 == flag){
                   flag = 1;
              }
         }
         
    } while (cPtr_strLengthOfK != NULL);
#if INS_DEBUG
    printf(" No of characters parsed : %d \n",((strlen(cPtr_buffer)-1)-ui_patternLength + 1));
    printf(" No of unhashed characters : %d \n",((strlen(cPtr_buffer)-1) - (ui_count) + 1) );
#endif
    /* Return the no.of.unhashed characters in the buffer */  
    return (((strlen(cPtr_buffer)-1) - (ui_count) + 1));
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
char *cPtr_readStringOfLengthK(char *cPtr_buffer,unsigned int ui_patternLength){
   
    char *cPtr_token = NULL;
    unsigned int ui_strlen = 0;
    
    ui_strlen = strlen(cPtr_buffer); 
    if( ((ui_strlen) - (ui_count )) >= ui_patternLength){
         cPtr_token = (char *)malloc(sizeof(char)*ui_patternLength+1);
         strncpy(cPtr_token,(const char *)(cPtr_buffer + ui_count),ui_patternLength);
         *(cPtr_token + ui_patternLength) = '\0';
         ui_count++;
         klen_times++;
    }
#if INS_DEBUG
    printf("%s : %d\n",cPtr_token,ui_count);
#endif
    return cPtr_token;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_updateBloomFilter(unsigned int ui_hashIndex){
    ui_bloomFilter[ui_hashIndex] += 1; 
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_writeBloomFilterToFile(){

    int i=0;

    FILE *fpBloomFilter = NULL;

    if( (fpBloomFilter = fopen("../data/bloomFilter.txt","w+")) == NULL){
         printf("ERROR: Cannot Open The File \n");
         exit(1);
    }
    
    for(i = 0 ; i < BLOOMFILTERSIZE; i++){
         fprintf(fpBloomFilter,"%d ",ui_bloomFilter[i]);
    }
    
    fclose(fpBloomFilter);
}
