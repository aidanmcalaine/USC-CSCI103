# contact: Mark Redekopp, David Pritchard
CFLAGS=-Wall -Wvla -Wshadow -Wunreachable-code -Wconversion -Wno-sign-conversion -Wno-sign-compare -Wno-write-strings -g
CC = g++
# if needed, install from http://bits.usc.edu/cs103/compile/ or use g++ or clang++
LDFLAGS =
SRCS = shapes.cpp bmplib.cpp
OBJ = $(SRCS:.cpp=.o)
DEMOSRC = demo.cpp bmplib.cpp
DEMOOBJ = $(DEMOSRC:.cpp=.o)

all: shapes demo

demo: $(DEMOOBJ)
	$(CC) $(CFLAGS) $(DEMOOBJ) -o demo

shapes: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o shapes

.cpp.o:
	$(CC) $(CFLAGS) -c $<

bmplib.o : bmplib.h

clean:
	rm -f *.o shapes *~

