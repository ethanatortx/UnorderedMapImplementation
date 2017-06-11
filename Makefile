CC=g++
CFLAGS=-std=c++14
SRCS=utility.hpp hashTable.hpp main.cpp

hashTable.o: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o hashTable.o

clean:
	del hashTable.o