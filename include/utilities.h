#ifndef _UTILITIES_
#define _UTILITIES_

/*
Version No: 1.0
*/

int i_randomNumberInRange(unsigned int, unsigned int);
char *cPtr_loadBloomFilter(FILE *);
char *cPtr_getPatternFromFile();
void v_writePatternToFile(char *);
void v_generatePatternsOfLengthK(int);

#endif
