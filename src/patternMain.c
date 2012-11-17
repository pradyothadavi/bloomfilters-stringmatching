#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include "inputString.h"
#include "utilities.h"
#include "patternString.h"

#define SETSIZE 10
#define MAXPATTERNLENGTH 1000
#define MINCOUNT 10
#define MAXCOUNT 30

#define SUCCESS 1
#define FAILURE 0
#define DEBUG 1

#define PATTERNFILELOCATION "../data/patterns.txt"

int main(int argc,char *argv[]){

    char c_alphabetSet[SETSIZE];
    char cArr_inputText[MAXPATTERNLENGTH];
    char c_temp;
    char c_choice;    
    char *cPtr_alphabetSet = NULL;

    int i_retVal = 0;
    int i_patternLength = 0;
    int i_noOfAlphabets = 0;
    int i = 0;
    int j = 0;

    FILE *fp = NULL;

    memset(&c_alphabetSet,'\0',SETSIZE);
    memset(&cArr_inputText,'\0',MAXPATTERNLENGTH);

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
              
    do{
         __fpurge(stdin);
         i_retVal = i_getAlphabetSet(c_alphabetSet);
         if(SUCCESS == i_retVal){
              do{
                   __fpurge(stdin);
                   i_patternLength = i_getPatternLength();
              } while ( (i_patternLength <= 0) || (i_patternLength > MAXPATTERNLENGTH) );
              cPtr_alphabetSet = c_alphabetSet;
              i_noOfAlphabets = strlen(cPtr_alphabetSet);
              for(i = 0;i < i_patternLength; i++){
                   cArr_inputText[i] = *(cPtr_alphabetSet+(i%i_noOfAlphabets));
              } 
#if DEBUG
    printf(" Input Text Before Shuffle: ");
    for(i = 0;i < i_patternLength; i++){
         printf("%c",cArr_inputText[i]);
    }
    printf("\n");
#endif    
              for(i = i_patternLength-1; i >= 1; i--){
                   j = i_randomNumberInRange(0,i);
                   c_temp = cArr_inputText[i];
                   cArr_inputText[i] = cArr_inputText[j];
                   cArr_inputText[j] = c_temp;
              }
#if DEBUG
    printf("\n Input Text After Shuffle: ");
    for(i = 0;i < i_patternLength; i++){
         printf("%c",cArr_inputText[i]);
    }
    printf("\n");
#endif
      
              for(i = 0; i < i_patternLength; i++){
                   fwrite(&cArr_inputText[i],sizeof(char),1,fp);
              }
              /* No.of.times the pattern must be present in the input string */
              j = i_randomNumberInRange(MINCOUNT,MAXCOUNT);
              fprintf(fp," %d \n",j);

         } else {

         } /* End of Outer if-else */

         __fpurge(stdin);
         printf("Press q to exit or any other key to enter more patterns : ");
         scanf("%c",&c_choice);
    } while ( (c_choice != 'q') );
    
    fclose(fp);

    return 0;
}
