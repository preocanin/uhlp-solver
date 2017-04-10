PROGRAM=uhlp
CXX=g++ 
CXXFLAGS= -std=c++1z -Wall

$(PROGRAM): bin ./lib/main.cpp parameter.o swarm.o particle.o
	$(CXX) $(CXXFLAGS) ./lib/main.cpp parameter.o swarm.o particle.o -o ./bin/$(PROGRAM)

bin: 
	mkdir bin

swarm.o: ./include/swarm.h ./lib/swarm.cpp ./include/parameter.h ./include/particle.h
	$(CXX) $(CXXFLAGS) ./lib/swarm.cpp -c

particle.o: ./include/particle.h ./lib/particle.cpp ./include/parameter.h
	$(CXX) $(CXXFLAGS) ./lib/particle.cpp -c

parameter.o: ./include/parameter.h ./lib/parameter.cpp
	$(CXX) $(CXXFLAGS) ./lib/parameter.cpp -c

.PHONY: clean 

clean:
	-rm *.o
	-rm -r bin



