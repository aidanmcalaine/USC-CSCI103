CXX = g++

all: queue.o mazeio.o queue_test maze

clean:
	rm -f *.o queue_test maze

%.o: %.cpp %.h
	$(CXX) -c $*.cpp -o $*.o

queue_test: queue.o queue_test.cpp
	$(CXX) queue.o queue_test.cpp -o queue_test

maze: maze.cpp queue.o mazeio.o
	$(CXX) $@.cpp queue.o mazeio.o -o $@

# bug: being treated as a terminal rule?
%: %.cpp queue.o mazeio.o
	$(CXX) $@.cpp queue.o mazeio.o -o $@

tar:
	tar cvf amaze.tar maze?.in *.cpp *.h readme.txt Makefile

