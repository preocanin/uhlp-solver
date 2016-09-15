#include "../include/parameter.h"

Parameter::Parameter(const std::string& path, InputFormat format) {
	std::ifstream f(path);
	if(f.is_open()) {
		format == FI_AP? readAp(f) : readRcab(f);
		f.close();
	} else {
		std::cerr << "Error: Opening file" << std::endl;
		std::exit(1);		
	}
}

void Parameter::readAp(std::ifstream& fin) {
	if(fin >> _n) {

	}
}

void Parameter::readRcab(std::ifstream& fin) {
    if(fin >> _n) {

	}
}
