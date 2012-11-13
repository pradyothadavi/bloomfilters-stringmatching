#ifndef _BLOOM_FILTER_
#define _BLOOM_FILTER_

#define FAILURE 0
#define SUCCESS 1

#define INS_DEBUG 0

#define BLOOMFILTERSIZE 100000

#define BUFFERSIZE 1000000

int i_performInsertOperation();
int i_insertIntoBloomFilter(char *,unsigned int);
char *cPtr_readStringOfLengthK(char *,unsigned int);
void v_updateBloomFilter(unsigned int);
char *cPtr_populateBuffer(unsigned int);
void v_writeBloomFilterToFile();

#endif
