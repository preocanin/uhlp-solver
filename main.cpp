#include <iostream>
#include <fstream>
#include <string>

#include "./include/parameter.h"
#include "./include/swarm.h"



int main(int argc, char **argv) {
	Parameter p;
	if(argc == 3) {
		std::string format(argv[1]);
		unsigned fsize = format.size();
		if(fsize == 3 || fsize == 4 || fsize == 5) {
			if(format == "-ap")
				p = Parameter(std::string(argv[2]),FI_AP);	
			if(format == "-cab" || format == "-rand")
				p = Parameter(std::string(argv[2]),FI_RCAB);
		}
		else
			std::cerr << "Unknown format of input" << std::endl;
	}
	else {
		std::cerr << "Error in arguments" << std::endl;
		std::cerr << "./main -[ap|cab|rand] file_name" << std::endl;
	}


	return 0;
}



