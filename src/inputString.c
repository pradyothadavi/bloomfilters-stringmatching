/*
Version No: 1.0
File Name: inputString.c
File Description: It has the code to produce the input text of specified length
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include "inputString.h"
#include "utilities.h"
#include "patternString.h"
#include "constants.h"

/*
Function Name: i_makeInputString
Description: It takes the alphabet set from the user and makes a string using 
             the alphabets in the set of length specified by MAXSIZE(constants.h).
Parameters: It does not take any parameters
Return Type: It returns a integer value.
             0 --> If there was an error in making the input string.
             1 --> If the input string was successfully formed.
*/
int i_makeInputString(){

	/* Declaration Section */
    char c_alphabetSet[SETSIZE];
    char *cPtr_pattern = NULL;

    unsigned int ui_count = 0;
    unsigned int ui_pos = 0;
    unsigned int ui_noOfPatterns = 0;

    int i_retVal = 0;
    int j = 0;
    int i = 0;
	/* End of Declaration Section */

    memset(&c_alphabetSet,'\0',SETSIZE);

    i_retVal = i_getAlphabetSet(c_alphabetSet);
    if(SUCCESS == i_retVal){
         v_writeTextToFile(c_alphabetSet);
         do{
              printf("Enter the no.of.patterns you want to insert: ");
              scanf("%u",&ui_noOfPatterns);
         } while ( ui_noOfPatterns <= 0);
         i_retVal = i_getPatternLength();
         for(i = 0;i < ui_noOfPatterns; i++){
              if( NULL != cPtr_pattern ){
                   free(cPtr_pattern);
              }
              cPtr_pattern = cPtr_getPattern(cPtr_pattern,(unsigned int)i_retVal);
              do{
                   printf("Enter no.of.times the pattern has to repeat in input text: ");
                   scanf("%u",&ui_count);
              }while(ui_count <= 0);
#if IP_DEBUG
    printf("The pattern is inserted at locations : ");
#endif
              do{
                   j = i_randomNumberInRange(0,MAXSIZE);
                   ui_pos = (ui_pos+j)%MAXSIZE;
#if IP_DEBUG
    printf("%d ",ui_pos);
#endif
                   v_writeTextToFileAtPosition(cPtr_pattern,ui_pos);
                   ui_count--;
              } while ( ui_count > 0);  
              printf("\n");
         }
                
    } else {
         return FAILURE;
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

#if IP_DEBUG
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
         exit(1);
    }

    memset(&cArr_inputText,'\0',MAXSIZE);
    i_noOfAlphabets = strlen(cPtr_alphabetSet);

    for(i = 0;i < MAXSIZE; i++){
         cArr_inputText[i] = *(cPtr_alphabetSet+(i%i_noOfAlphabets));
    }

    /*Fisher-Yates Shuffle Algorithm */
    for(i = MAXSIZE-1; i >= 1; i--){
         j = i_randomNumberInRange(0,i);
         c_temp = cArr_inputText[i];
         cArr_inputText[i] = cArr_inputText[j];
         cArr_inputText[j] = c_temp;
    }

    for(i = 0; i < MAXSIZE; i++){
         fwrite(&cArr_inputText[i],sizeof(char),1,fp);
    }
    
    fclose(fp);   
}

/*
Function Name: v_writeTextToFileAtPosition
Description: It writes the pattern into the input string at the specified posit-
             -ion.
Parameters: Two parameters
            1) Pattern to be written
            2) Position in the file where the pattern is to be written
Return Type: void
*/
void v_writeTextToFileAtPosition(char *cPtr_charsToWrite, unsigned int ui_pos){

    unsigned int ui_noOfCharacters = 0;

    int i = 0;

    FILE *fp = NULL;

    if( (fp=fopen(FILELOCATION,"r+")) == NULL){
         printf("ERROR: Cannot Open The File \n");
         exit(1);
    }

    if( (fseek(fp,0,SEEK_SET)) == -1){
         printf("ERROR: Cannot move the file pointer to the starting of the file \n");
    }
    if( (fseek(fp,ui_pos,SEEK_SET)) == -1){
         printf("ERROR: Cannot move the file pointer to the correct location \n");
    } else {
         ui_noOfCharacters = strlen(cPtr_charsToWrite);
         for( i = 0; i < ui_noOfCharacters; i++){
              fwrite(&(*(cPtr_charsToWrite+i)),sizeof(char),1,fp);
         }
    }

    fclose(fp);
}

/*
Function Name: i_getPatternLength
Description: It gets the length of the pattern from the user
Parameters: No parameters
Return Type: It returns the value entered by user ( pattern length )
*/
int i_getPatternLength(){

    int i_patternLength = 0;
    int i_retVal = 0;
    do{
         __fpurge(stdin);
         printf("Enter the value of k [length of pattern]: ");
         i_retVal = scanf("%d",&i_patternLength);
    } while( (0 == i_retVal) || (i_patternLength <= 0) );
    
    return i_patternLength;
}

/*
Function Name: cPtr_getPattern
Description: It gets the pattern to be inserted into the input string from the 
             console.
Parameters: A pointer which will hold the pattern to be inserted and length of 
            the pattern
Return Type: It returns the memory location where the pattern to be inserted is
             stored.
*/
char *cPtr_getPattern(char *cPtr_pattern, unsigned int ui_patternLength){

    char *cPtr_retVal = NULL;
    unsigned int ui_length = 0;

    if(cPtr_pattern != NULL){
         cPtr_pattern = NULL;
    }
    cPtr_pattern = (char *)malloc(sizeof(char)*ui_patternLength);
    do{
         printf("Enter the pattern of length %d : ",ui_patternLength);
         __fpurge(stdin);
         if( (cPtr_retVal = fgets(cPtr_pattern,ui_patternLength+1,stdin)) == NULL){
              printf("ERROR: Cannot read the pattern \n");
         }
         ui_length = strlen(cPtr_pattern);
         if( *(cPtr_pattern + ui_length - 1) == '\n'){
              *(cPtr_pattern + ui_length - 1) = '\0';
         }
    } while ( ui_length != ui_patternLength );
    
#if IP_DEBUG
    ui_length = 0;
    printf("DEBUG: The pattern is ");
    while( *(cPtr_pattern + ui_length) != '\0'){
         printf("%c",*(cPtr_pattern+ui_length));
         ui_length++;
    }
    printf("\n");
#endif
    return cPtr_pattern;   
}
