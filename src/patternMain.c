/*
Version No: 1.0
File Name: patternMain.c
File Description: The file has the code to generate patterns
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include "inputString.h"
#include "utilities.h"
#include "patternString.h"
#include "constants.h"

#define SUCCESS 1
#define FAILURE 0

#define DEBUG 0 /* Change it to 1 to print debug statements */

#define MINCOUNT 05 /* Lower limit of the parameter 't' */
#define MAXCOUNT 20 /* Upper limit of the parameter 't' */

/*
Function Name: main
Description: It produces patterns of length specified by PATTERNLENGTH ( present
             in constants.h ) file and also a random number between the 
             range [MINCOUNT,MAXCOUNT] is associated with a pattern and stored 
         in file at the location specified by PATTERNFILELOCATION (constants.h )
Parameters: No parameters
Return Type: int
*/
int main(int argc,char *argv[]){

		/* Declaration Section */
    char c_alphabetSet[SETSIZE];
    char cArr_inputText[PATTERNLENGTH];
    char c_temp;    
    char *cPtr_alphabetSet = NULL;

    int i_retVal = 0;
    int i_noOfPatterns = 0;
    int i_noOfAlphabets = 0;
    int i = 0;
    int j = 0;

    FILE *fp = NULL;
		/* End of declaration section */
		
    memset(&c_alphabetSet,'\0',SETSIZE);
    memset(&cArr_inputText,'\0',PATTERNLENGTH);

    /* Clear the previous contents in the file */
    fp = fopen(PATTERNFILELOCATION,"r");
    if( fp != NULL){
         fclose(fp);
         fp = fopen(PATTERNFILELOCATION,"w");
         fclose(fp);
    }         
    if( (fp = fopen(PATTERNFILELOCATION,"a+")) == NULL){
         printf("ERROR: Cannot create the file \n");
         exit(1);
    }
    __fpurge(stdin);
    i_retVal = i_getAlphabetSet(c_alphabetSet);
    __fpurge(stdin);
    do{
         printf("Enter the no.of.patterns to be generated: ");
         scanf("%d",&i_noOfPatterns);
    }while(i_noOfPatterns <= 0);
    cPtr_alphabetSet = c_alphabetSet;
    i_noOfAlphabets = strlen(cPtr_alphabetSet);          
    do{
         if(SUCCESS == i_retVal){          
              for(i = 0;i < PATTERNLENGTH; i++){
                   cArr_inputText[i] = *(cPtr_alphabetSet+(i%i_noOfAlphabets));
              } 
#if DEBUG
    printf(" Input Text Before Shuffle: ");
    for(i = 0;i < PATTERNLENGTH; i++){
         printf("%c",cArr_inputText[i]);
    }
    printf("\n");
#endif    
		    /* Fisher-Yates Shuffle Algorithm */
              for(i = PATTERNLENGTH-1; i >= 1; i--){
                   j = i_randomNumberInRange(0,i);
                   c_temp = cArr_inputText[i];
                   cArr_inputText[i] = cArr_inputText[j];
                   cArr_inputText[j] = c_temp;
              }
#if DEBUG
    printf("\n Input Text After Shuffle: ");
    for(i = 0;i < PATTERNLENGTH; i++){
         printf("%c",cArr_inputText[i]);
    }
    printf("\n");
#endif
      
              for(i = 0; i < PATTERNLENGTH; i++){
                   fwrite(&cArr_inputText[i],sizeof(char),1,fp);
              }
              /* No.of.times the pattern must be present in the input string */
              j = i_randomNumberInRange(MINCOUNT,MAXCOUNT);
              fprintf(fp," %d \n",j);

         } else {

         } /* End of Outer if-else */
         
         i_noOfPatterns--;
    } while ( i_noOfPatterns > 0 );
    
    fclose(fp);

    return 0;
}
