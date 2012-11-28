/*
Version No: 1.0
File Name: insertOpsMain.c
File Description: The file has the code for the main function to create the data
     structure 'Bloom-Filter' for a specific input string.
*/

#include <stdio.h>

#include "main.h"
#include "inputString.h"
#include "insertOps.h"

/*
Function Name: main
Description: It calls 3 modules namely 
             1) i_makeInputString ( To produce the input string )
             2) i_performInsertOperation ( To perform insertion into the Bloom-
                                           -Filter )
             3) v_writeBloomFilter ( To save the Bloom-Filter for further use )
Parameters: No parameters
Return Type: int
*/
int main(int argc,char *argv[]){

    int i_retVal = 0;

    i_retVal = i_makeInputString();
    if(SUCCESS == i_retVal){
         i_retVal = i_performInsertOperation();
    } else {
         printf("ERROR: Insert Operation Failed ! \n");
    }
    if(i_retVal > 0){
         v_writeBloomFilterToFile();
    }
    return 0;
}
