#ifndef _PARAMS

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define _PARAMS

enum InputFormat {FI_AP,FI_RCAB};

class Parameter {
	public:
		Parameter(const std::string&,InputFormat);

	private:
	    int _n;
		float _alpha;
		float _hnp; //Hub-Node price	
		float _nhp; //Node-Hub price  
	    std::vector<std::vector<float> > _flow; // Flow between nodes i and j
		std::vector<float> _fcost; // Cost of establishing hub in node i	
	
		InputFormat _format; //Indicating format of input	

		void readAp(std::ifstream&);
		void readRcab(std::ifstream&);
};

#endif
