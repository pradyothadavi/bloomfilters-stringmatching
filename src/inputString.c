/*
Version No: 1.0
*/
#include <stdio.h>
#include <string.h>

#include "inputString.h"
#include "utilities.h"

/*
Function Name: i_makeInputString
Description: It takes the alphabet set from the user/admin and makes a string
             using the alphabets in the set of length 10^8. The user can later
             search for patterns that might occur in this string.
Parameters: It does not take any parameters
Return Type: It returns a integer value.
             0 --> If there was an error in making the input string.
             1 --> If the input string was successfully formed.
*/
int i_makeInputString(){

    char c_alphabetSet[SETSIZE];

    int i_retVal = 0;

    memset(&c_alphabetSet,'\0',SETSIZE);

    i_retVal = i_getAlphabetSet(c_alphabetSet);
    if(SUCCESS == i_retVal){
         v_writeTextToFile(c_alphabetSet);
    }
    return SUCCESS;
}

/*
Function Name: i_getAlphabetSet
Description: The function obtains the alphabet set from user, using which the 
             input String is prepared.
Parameters: It takes a char pointer, pointing to the array having the alphabets.
Return Type: It returns a integer value.
             0 --> If there was an error in getting alphabet set from user.
             1 --> If the input alphabet set was successfully formed.
*/
int i_getAlphabetSet(char *cPtr_alphabetSet){

    char *cPtr_retVal = NULL;
    int i_length = 0;
    int i_count = 0;

    do{
         printf("Enter all the characters of the alphabet set : ");
         if((cPtr_retVal = fgets(cPtr_alphabetSet,SETSIZE+1,stdin)) == NULL){
              printf("ERROR: Cannot read the input string \n");
              i_count++;
         }
    }while( (NULL == cPtr_retVal) && (i_count < 4) );
 
    if(cPtr_retVal != NULL){
         i_length =  strlen(cPtr_alphabetSet);
         if( *(cPtr_alphabetSet + i_length-1) == '\n'){
              *(cPtr_alphabetSet + i_length-1) = '\0';
         }
    }

#if DEBUG
    printf(" Alphabet Set : ");
    while(*cPtr_retVal != '\0'){
         printf("%c",*cPtr_retVal);
         cPtr_retVal++;
    }
    printf("\n");
#endif

    if(4 == i_count){
         return FAILURE;
    }         
    return SUCCESS;
}

/*
Function Name: v_writeTextToFile
Description: Using the alphabet set, the function prepares the input string and
             stores it in a file.
Parameters: It takes a single parameter, a pointer pointing to the array 
            containing the alphabet set.
Return Type: It returns void
*/
void v_writeTextToFile(char *cPtr_alphabetSet){

    char cArr_inputText[MAXSIZE];
    char c_temp;

    int i_noOfAlphabets = 0;
    int i = 0;
    int j = 0;
 
    FILE *fp = NULL;

    if( (fp = fopen(FILELOCATION,"w+")) == NULL){
         printf("ERROR: Cannot create the file \n");
    }

    memset(&cArr_inputText,'\0',MAXSIZE);
    i_noOfAlphabets = strlen(cPtr_alphabetSet);

    for(i = 0;i < MAXSIZE; i++){
         cArr_inputText[i] = *(cPtr_alphabetSet+(i%i_noOfAlphabets));
    }
#if DEBUG
    printf(" Input Text Before Shuffle: ");
    for(i = 0;i < MAXSIZE; i++){
         printf("%c",cArr_inputText[i]);
    }
    printf("\n");
#endif

    for(i = MAXSIZE; i >= 1; i--){
         j = i_randomNumberInRange(0,i);
#if DEBUG
    printf("%d ",j);
#endif
         c_temp = cArr_inputText[i];
         cArr_inputText[i] = cArr_inputText[j];
         cArr_inputText[i] = c_temp;
#if DEBUG
    printf("%c %c \n",cArr_inputText[i],cArr_inputText[j]);
#endif       
    }
#if DEBUG
    printf("\n Input Text After Shuffle: ");
    for(i = 0;i < MAXSIZE; i++){
         printf("%c",cArr_inputText[i]);
    }
    printf("\n");
#endif

    if( (fputs(cArr_inputText,fp)) == EOF){
         printf("ERROR: Cannot write data to the file \n");
    }

    fclose(fp);   
}
