CC=g++
CFLAGS = -c -pedantic -error -Wall

all: ConnectFour

ConnectFour: main.o ConnectFour.o 
	$(CC) -std=c++11 -o ConnectFour ConnectFour.o main.o

main.o: main.cpp
	$(CC) -std=c++11 $(CFLAGS) main.cpp

ConnectFour.o: ConnectFour.cpp
	$(CC) -std=c++11 $(CFLAGS) ConnectFour.cpp

clean: 
	rm -rf *o ConnectFour
