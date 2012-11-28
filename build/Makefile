BFDIR	=	..

CC	=	gcc

CFLAGS	=	-g -I$(BFDIR)/include -ansi -pedantic -Wall -Werror

INSERT_OBJS	=	$(BFDIR)/src/patternString.o $(BFDIR)/src/utilities.o $(BFDIR)/src/inputString.o $(BFDIR)/src/insertOps.o $(BFDIR)/src/hashFunctions.o $(BFDIR)/src/insertOpsMain.o

SEARCH_OBJS	=	$(BFDIR)/src/utilities.o $(BFDIR)/src/inputString.o $(BFDIR)/src/patternString.o $(BFDIR)/src/insertOps.o $(BFDIR)/src/hashFunctions.o $(BFDIR)/src/searchOps.o $(BFDIR)/src/kmp.o $(BFDIR)/src/searchOpsMain.o

PATTERN_OBJS	=	$(BFDIR)/src/inputString.o $(BFDIR)/src/patternString.o $(BFDIR)/src/utilities.o $(BFDIR)/src/patternMain.o

INSERT_TARGET	=	insertBloomFilter

SEARCH_TARGET	=	searchBloomFilter

PATTERN_TARGET	=	generatePatterns

$(INSERT_TARGET):	$(INSERT_OBJS)
	$(CC) -o $(BFDIR)/bin/$@ $(INSERT_OBJS) -lm	
	mv $(BFDIR)/src/*.o $(BFDIR)/bin

$(INSERT_OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(SEARCH_TARGET):	$(SEARCH_OBJS)
	$(CC) -o $(BFDIR)/bin/$@ $(SEARCH_OBJS)	-lm
	mv $(BFDIR)/src/*.o $(BFDIR)/bin

$(SEARCH_OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(PATTERN_TARGET):	$(PATTERN_OBJS)
	$(CC) -o $(BFDIR)/bin/$@ $(PATTERN_OBJS)	
	mv $(BFDIR)/src/*.o $(BFDIR)/bin

$(PATTERN_OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(BFDIR)/bin/*.o core $(BFDIR)/src/*.o core $(BFDIR)/bin/$(INSERT_TARGET) $(BFDIR)/bin/$(SEARCH_TARGET) $(BFDIR)/bin/$(PATTERN_TARGET) $(BFDIR)/data/*

