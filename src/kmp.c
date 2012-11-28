#include "kmp.h"
#include "insertOps.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kmp **kmpFind;
unsigned int ui_numStrings = 0;
unsigned int matchCount=0;

int i_getKmpStrings(){

    unsigned int i=0,j;
    FILE * kmpReadFp;
 
    kmpReadFp=fopen(PATTERNFILELOCATION,"r");
    if(NULL == kmpReadFp){
    	printf("Error in opening probable Strings file\n");
    	return 0;
    }else{
     
        kmpFind=(kmp**)malloc(sizeof(kmp*)*ui_numStrings);
    
        for(i=0;i<ui_numStrings;i++){
            kmpFind[i]=(kmp*)malloc(sizeof(kmp)*ui_numStrings);
            kmpFind[i]->kmpStrings=(char*)malloc(sizeof(char)*(PATTERNLENGTH+1));
            kmpFind[i]->pi=(int*)malloc(sizeof(int)*(PATTERNLENGTH+1));
            memset((void *)kmpFind[i]->kmpStrings,'\0',PATTERNLENGTH+1);
            memset((void *)kmpFind[i]->pi,0,4*(PATTERNLENGTH+1));
        }
        
        for(i=0;i<ui_numStrings;i++){
            fscanf(kmpReadFp,"%s %u \n",kmpFind[i]->kmpStrings+1,&(kmpFind[i]->exp_count));
            kmpFind[i]->pi=compute_prefix_function(kmpFind[i]->kmpStrings,i);
        }

        for(i=0;i<ui_numStrings;i++){
            for(j=1;j<PATTERNLENGTH+1;j++){
#if KMP_DEBUG
                printf("%d\t",kmpFind[i]->pi[j]);
#endif
            }
        }
        
        
        return 1;
    }
    
}

int *compute_prefix_function(char *pattern,unsigned int iteration){

    int k = 0;
    int i = 0;

    if (!(kmpFind[iteration]->pi))
  	return NULL;

    kmpFind[iteration]->pi[1] = k;
    for (i = 2; i <= PATTERNLENGTH; i++) {
	while (k > 0 && pattern[k+1] != pattern[i])
	    k = kmpFind[iteration]->pi[k];
        if (pattern[i] == pattern[k+1])
	    k++;
	kmpFind[iteration]->pi[i] = k;
    }
    return kmpFind[iteration]->pi;
}

unsigned int ui_kmp(char* cPtr_buffer){

    unsigned int i,j;
    unsigned int buff_len=strlen(cPtr_buffer);

    FILE *fpKmpOutput = NULL;

    for(i=0;i<ui_numStrings;i++){
        
        int k = 0;
#if KMP_DEBUG
        unsigned int result=-1;
#endif
	if (!(kmpFind[i]->pi))
		/*result=-1;*/ break;
	for (j = 1; j <= buff_len; j++) {
	    while (k > 0 && *(kmpFind[i]->kmpStrings+(k+1)) != *(cPtr_buffer+j-1))
		k = kmpFind[i]->pi[k];
		
	    if ( *(cPtr_buffer+j-1) == *(kmpFind[i]->kmpStrings+k+1))
		k++;
		
	    if (k == PATTERNLENGTH) {
		
#if KMP_DEBUG
    result=(j-1)-PATTERNLENGTH;
    printf("res %d\n",result);
#endif
		kmpFind[i]->count++;
   		k=kmpFind[i]->pi[k];
	    }
	   
	}
	
    }
    fpKmpOutput = fopen("../data/finalPatterns.txt","w+");
    for(i=0;i<ui_numStrings;i++){
#if KMP_DEBUG
    printf("count %d exp coount %d \t",kmpFind[i]->count,kmpFind[i]->exp_count);
    printf("PERF %s\n",kmpFind[i]->kmpStrings+1);
#endif
         if(kmpFind[i]->count >= kmpFind[i]->exp_count ){
              fprintf(fpKmpOutput,"%s %u \n",kmpFind[i]->kmpStrings+1,kmpFind[i]->count);
         }
    }
    fclose(fpKmpOutput);

    return ( (PATTERNLENGTH-1));
 }

int i_performKmpSearch(unsigned int ui_numStr){

    unsigned int ui_KmpFileOffset = 0;
    int getStrings=-1;
    char *cPtr_buffer = NULL;
   
    ui_numStrings=ui_numStr;
       
    getStrings=i_getKmpStrings();

    if(1 == getStrings){
        do{
         /* Read from the file where the input data string is stored and 
            populate into a buffer for KMP matching.
         */
         cPtr_buffer = cPtr_populateBuffer(ui_KmpFileOffset);
         
         if( NULL != cPtr_buffer){
             /* Populate the Bloom Filter */
              ui_KmpFileOffset = ui_kmp(cPtr_buffer);
         }

    } while (cPtr_buffer != NULL);
    }/*end of if */
    
    
return 1;
}
