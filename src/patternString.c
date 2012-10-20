
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

/*
Function Name:
Description:
Parameters:
Return Type:
*/
int i_getPatternLength(){

    int i_patternLength = 0;
    int i_retVal = 0;
    do{
         __fpurge(stdin);
         printf("Enter the length of the pattern to be searched from the string: ");
         i_retVal = scanf("%d",&i_patternLength);
    } while( (0 == i_retVal) || (i_patternLength <= 0) );
    
    return i_patternLength;
}

/*
Function Name:
Description:
Parameters:
Return Type:
*/
void v_computePatterns(unsigned int ui_patternLength,char *cPtr_alphabetSet){
    
}

/*
Function Name:
Description:
Parameters:
Return Type:
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
    
#if DEBUG
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
