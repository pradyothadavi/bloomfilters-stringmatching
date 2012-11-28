/*
Version No: 1.0
*/

#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"
#include "searchOpsMain.h"
#include "searchOps.h"
#include "kmp.h"

int main(){

    unsigned int ui_noOfPatterns = 0;
    unsigned int ui_choice = 0;

    printf("------------------ Menu ------------------ \n");
    printf("1) Search Patterns Using BloomFilter & KMP \n");
    printf("2) Search Patterns Using KMP Only \n");
    printf("------------------------------------------ \n");
    printf("Enter the choice : ");
    scanf("%u",&ui_choice);

    switch(ui_choice){
    
         case 1: ui_noOfPatterns = ui_performSearchOps();
                 if( ui_noOfPatterns > 0 ){
                      i_performKmpSearch(ui_noOfPatterns);
                 }
                 break;

         case 2: printf("Enter the no.of.patterns present in Pattern File: ");
                 scanf("%u",&ui_noOfPatterns);
                 i_performKmpSearch(ui_noOfPatterns);
                 break;

         default:printf("Invalid Option \n");
    }
    
    return 0;
}
