#ifndef _INPUT_STRING_
#define _INPUT_STRING_

/*
Version No: 1.0
*/

#define SUCCESS 1
#define FAILURE 0

#define SETSIZE 10
#define MAXSIZE 500

#define FILELOCATION "../data/inputText.txt"

int i_makeInputString();
int i_getAlphabetSet(char *);
void v_writeTextToFile(char *);
void v_writeTextToFileAtPosition(char *,unsigned int);
#endif

