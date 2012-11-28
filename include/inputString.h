#ifndef _INPUT_STRING_
#define _INPUT_STRING_

/*
Version No: 1.0
*/

#define SUCCESS 1
#define FAILURE 0

#define IP_DEBUG 0

int i_makeInputString();
int i_getAlphabetSet(char *);
void v_writeTextToFile(char *);
void v_writeTextToFileAtPosition(char *,unsigned int);
int i_getPatternLength();
void v_computePatterns(unsigned int,char *);
char *cPtr_getPattern(char *,unsigned int);

#endif

