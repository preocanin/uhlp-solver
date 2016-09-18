CC = g++ 
CFLAGS = -std=c++0x -Wall

main: main.cpp parameter.o 
	$(CC) $(CFLAGS) main.cpp parameter.o -o main 

parameter.o: ./include/parameter.h ./lib/parameter.cpp
	$(CC) $(CFLAGS) ./lib/parameter.cpp -c

