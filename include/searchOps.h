#ifndef _SEARCH_OPS_
#define _SEARCH_OPS_

#include "constants.h"

#define SUCCESS 1
#define FAILURE 0

#define SEARCH_DEBUG 1

struct SearchPattern{
    char c_pattern[PATTERNLENGTH+1];
    unsigned int ui_noOfTimes;
    int i_flag;
    struct SearchPattern *nextPattern;
};

unsigned int ui_performSearchOps();
void v_loadBloomFilter();
struct SearchPattern *s_getPatternsFromFile();
int i_hashPattern(char *,unsigned int,int);
void v_writeToFile(struct SearchPattern *);
#endif
