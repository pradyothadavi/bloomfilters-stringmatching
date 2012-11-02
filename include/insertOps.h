#ifndef _BLOOM_FILTER_
#define _BLOOM_FILTER_

#define FAILURE 0
#define SUCCESS 1

int i_createBloomFilter();
int i_performInsertOperation();
int i_insertIntoBloomFilter(char *,unsigned int);
char *cPtr_readStringOfLengthK(char *,unsigned int);
void v_updateBloomFilter(unsigned long);
char *cPtr_populateBuffer(unsigned int);
#endif
