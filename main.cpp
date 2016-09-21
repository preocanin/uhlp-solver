#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <set>

#include "./include/parameter.h"
#include "./include/swarm.h"

void errorExit(const std::string&);

int main(int argc, char **argv) {
	int rseed;
	Parameter p;

	if(argc == 4) {
		std::string format(argv[1]);
		unsigned fsize = format.size();
		if(fsize == 3 || fsize == 4 || fsize == 5) {
			if(format == "-ap")
				p = Parameter(std::string(argv[2]),FI_AP);	
			if(format == "-cab" || format == "-rand")
				p = Parameter(std::string(argv[2]),FI_RCAB);
		}
		else
			errorExit("Unknown format of input");

		rseed = std::atoi(argv[3]);
		if(rseed < 0) 
			errorExit("Seed must be greater then zero");
		else	
		    std::srand(rseed);	
	}
	else {
		std::cerr << "Error in arguments" << std::endl;
		errorExit("./main -[ap|cab|rand] file_name seed_integer");
	}

	std::vector<int> v(10,-1);
	Particle p1(p,v);

	return 0;
}


void errorExit(const std::string& msg) {
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}
