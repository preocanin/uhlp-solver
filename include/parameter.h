#ifndef _PARAMS

#define _PARAMS

#include <vector>
#include <fstream>

enum InputFormat {FI_AP,FI_RCAB};

class Parameter {
	public:
		InputFormat _format; //Indicating format of input	
		Parameter(const std::string&,InputFormat);

		~Parameter() {}
	private:
	    int _n;
		float _alpha;
		float _c; //Node-Hub price	
		float _d; //Hub-Node price 
	
		//In AP instances _cij will be used as matrix of distances between nodes
		//while n CAB and RAND instances will be used as matrix of costs 
	   	std::vector<std::vector<float> > _cij; 	
	    std::vector<std::vector<float> > _wij; // Flow between nodes i and j
		std::vector<float> _fi; // Cost of establishing hub in node i	

		void readAp(std::ifstream&);
		void readRcab(std::ifstream&);
		void errorMessage(const std::string&) const;
};

#endif
