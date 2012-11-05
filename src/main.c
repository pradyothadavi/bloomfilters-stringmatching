/*
Version No: 1.0
*/

#include <stdio.h>

#include "main.h"
#include "inputString.h"
#include "insertOps.h"

int main(int argc,char *argv[]){

    int i_retVal = 0;

    i_retVal = i_makeInputString();
    if(SUCCESS == i_retVal){
         i_retVal = i_performInsertOperation();
    } else {

    }
    return 0;
}
