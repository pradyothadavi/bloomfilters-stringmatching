BFDIR	=	..

CC	=	gcc

CFLAG	=	-g -I$(BFDIR)/include -ansi -pedantic -Wall -Werror

OBJS	=	

TARGET	=	bloomFilter

$(TARGET):	$(OBJS)
	$(CC) -o $(BFDIR)/bin/@ $(OBJS)	
	mv $(BFDIR)/src/*.o $(BFDIR)/bin

$(OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: bloomFilter

clean:
	rm -f $(BFDIR)/bin/*.o -core $(BFDIR)/bin/$(TARGET)

