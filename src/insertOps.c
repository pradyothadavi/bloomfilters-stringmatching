/*
Function Name:
Description:
Parameters:
Return Type:
*/
int i_performInsertOperation(){

    unsigned int ui_patternLength = 0;
    unsigned int ui_fileOffset = 0;
    int i_retVal = FAILURE;
    
    /* Create a bloom filter of size of the largest array that can be created
       in the machine on which the application will run.
    */
    i_retVal=i_createBloomFilter();

    /* Get the length of the pattern from the user and store it in a variable*/
    if(SUCCESS == i_retVal){
         
         do{
              /* Read from the file where the input data string is stored and
                 populate into a buffer.
              */
              cPtr_buffer = cPtr_populateBuffer(ui_fileOffset);

              /* Populate the Bloom Filter */
              ui_fileOffset = i_insertIntoBloomFilter(cPtr_buffer,ui_patternLength);

         } while (cPtr_buffer != NULL);
                 
    }

    /* Return the length of the pattern entered by the user */
    return ui_patternLength;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
int i_createBloomFilter(){

    return SUCCESS;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
char *cPtr_populateBuffer(unsigned int ui_offset){

    char *cPtr_dummy = NULL;

    return cPtr_dummy;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
int i_insertIntoBloomFilter(char *cPtr_buffer,ui_patternLength){

    char *cPtr_strLengthOfK = NULL;
    
    unsigned int ui_count = 0;
    unsigned long ul_hashIndex = -1;

    do{
         /* Read from buffer a string of length k */
         cPtr_strLengthOfK = cPtr_readStringOfLengthK(cPtr_buffer,ui_patternLength);

         ui_count++;

         /* Perform hashing using hash function 01 */
         ul_hashIndex = hashFunctionOne(cPtr_strLengthOfK);
         v_updateBloomFilter(ul_hashIndex);

    } while (cPtr_strLengthOfK != NULL);
    
    /* Return the no.of.unhashed characters in the buffer */  
    return (strlen(cPtr_buffer) - (ui_count-1)*ui_patternLength);
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
char *cPtr_readStringOfLengthK(char *cPtr_buffer,unsigned int ui_patternLength){
   
    char *cPtr_dummy = NULL;

    return cPtr_dummy;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_updateBloomFilter(unsigned long ul_hashIndex){

}
