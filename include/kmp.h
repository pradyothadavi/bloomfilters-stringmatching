#ifndef _KMP_H_
#define _KMP_H_

#define KMP_DEBUG 0

typedef struct kmpCheck{
    char *kmpStrings;
    int *pi;
    unsigned int count,exp_count;
}kmp;

int *compute_prefix_function(char*,unsigned int);

unsigned int ui_kmp(char*);

int i_getKmpStrings();

int i_performKmpSearch(unsigned int);

#endif


