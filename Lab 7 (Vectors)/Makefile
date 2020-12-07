CC = g++ -g
ALL = bigint.o test0 test1 test2 copies fib 2pow fact

all: $(ALL)

bigint.o: bigint.cpp bigint.h
	$(CC) -c $< -o $@

test0: bigint.o test0.cpp
	$(CC) $^ -o $@

test1: bigint.o test1.cpp
	$(CC) $^ -o $@

test2: bigint.o test2.cpp
	$(CC) $^ -o $@

copies: bigint.o copies.cpp
	$(CC) $^ -o $@

fib: bigint.o fib.cpp
	$(CC) $^ -o $@

2pow: bigint.o 2pow.cpp
	$(CC) $^ -o $@

fact: bigint.o fact.cpp
	$(CC) $^ -o $@

bases: bigint.o bases.cpp
	$(CC) $^ -o $@

badaccess: bigint.o badaccess.cpp
	$(CC) $^ -o $@

clean:
	rm -f $(ALL) badaccess

tar:
	rm -f lab-bigint.tar
	tar cvf lab-bigint.tar Makefile bigint.h test0.cpp test1.cpp \
                copies.cpp fib.cpp 2pow.cpp fact.cpp bases.cpp test2.cpp
