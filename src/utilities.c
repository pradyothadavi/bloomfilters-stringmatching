/*
Version No: 1.0
*/

#include <stdio.h>
#include <stdlib.h>

/*
Function Name: i_randomNumberInRange
Description: Generates a random number between the specified range
Parameters: It takes two parameters, the upper and lower limit of the range.
Return Type: it returns an integer with the specified range
*/
int i_randomNumberInRange(unsigned int ui_min, unsigned int ui_max){
    
    int i_baseRandom = 0;
    int i_range = 0;
    int i_remainder = 0;
    int i_bucket = 0;

    i_baseRandom = rand(); /* in [0, RAND_MAX] */
  
    if (RAND_MAX == i_baseRandom){
         return i_randomNumberInRange(ui_min, ui_max);
    }
  
    /* now guaranteed to be in [0, RAND_MAX) */
    i_range = ui_max - ui_min,
    i_remainder = RAND_MAX % i_range,
    i_bucket = RAND_MAX / i_range;
    /* There are range buckets, plus one smaller interval within remainder
       of RAND_MAX */
    if (i_baseRandom < RAND_MAX - i_remainder) {
         return ui_min + i_baseRandom/i_bucket;
    } else {
         return i_randomNumberInRange(ui_min, ui_max);
    }
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
char *cPtr_loadBloomFilter(FILE *bloomFp){

    char *cPtr_dummy = NULL;

    return cPtr_dummy;
}

/*
Function Name:
Description: Read the patterns which are stored in a file. Each time one pattern
             is returned.
Parameters:
Return Type:
*/
char *cPtr_getPatternFromFile(){

    char *cPtr_dummy = NULL;

    return cPtr_dummy;


}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_writePatternToFile(char *cPtr_pattern){

}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_generatePatternsOfLengthK(int i_patternLength){

    if(i_patternLength <= 0){
         printf("ERROR: Cannot Generate Pattern As Length Is Zero \n");
         return;
    }
}
