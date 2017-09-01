
## Created by Anjuta

CC = cc
CFLAGS = -g -Wall
OBJECTS = bmicalc.o
INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

all: bmicalc

bmicalc: $(OBJECTS)
	$(CC) -o bmicalc $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
