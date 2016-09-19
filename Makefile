CC = g++ 
CFLAGS = -std=c++0x -Wall

main: main.cpp parameter.o swarm.o
	$(CC) $(CFLAGS) main.cpp parameter.o swarm.o -o main 

swarm.o: ./include/swarm.h ./lib/swarm.cpp ./include/parameter.h
	$(CC) $(CFLAGS) ./lib/swarm.cpp -c

parameter.o: ./include/parameter.h ./lib/parameter.cpp
	$(CC) $(CFLAGS) ./lib/parameter.cpp -c

.PHONY: clean

clean:
	-rm *.o main


