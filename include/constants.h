#ifndef _CONSTS_
#define _CONSTS_

#define SETSIZE 10 /* Maximum no.of.characters in the alphabet set */

#define MAXSIZE 1000000 /* No.of.characters in the input string */

#define BLOOMFILTERSIZE 100000 /* This should be 1/4th of the input string */

#define PATTERNLENGTH 200 /* Value of K ( Length of the pattern ) */

#define BUFFERSIZE 100000 /* Size of the buffer into which input string is read */

#define FILELOCATION "../data/inputText.txt" /* Location where the input string is present */

#define BLOOMFILTERLOCATION "../data/bloomFilter.txt" /* Location where the bloom filter is stored */

#define PATTERNFILELOCATION "../data/patterns.txt" /* Location where the patterns to checked are present */

#define ELIGIBLEPATTERNS "../data/probablePatterns.txt" /* Locations where patterns shortlisted bloomfilter are present */

#endif
