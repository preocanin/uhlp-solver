#ifndef _PARAMS

#define _PARAMS

#include <vector>
#include <fstream>

enum InputFormat {FI_AP,FI_RCAB};

class Parameter {
	public:
		InputFormat _format; //Indicating format of input	
		Parameter() {}
		Parameter(const std::string&,InputFormat);


		int getN() const {return _n;}
		double getAlpha() const {return _alpha;}
		double getNodeHabPrice() const {return _c;}
		double getHabNodePice() const {return _d;}
		double getFi(const int i) const {return _fi[i];}
		double getWij(const int i, const int j) const {return _wij[i][j];}
		double getCij(const int i, const int j) const {return _cij[i][j];}

		~Parameter() {}
	private:
	    int _n;
		double _alpha;
		double _c; //Node-Hub price	
		double _d; //Hub-Node price 
	
		//In AP instances _cij will be used as matrix of distances between nodes
		//while n CAB and RAND instances will be used as matrix of costs 
	   	std::vector<std::vector<double> > _cij; 	
	    std::vector<std::vector<double> > _wij; // Flow between nodes i and j
		std::vector<double> _fi; // Cost of establishing hub in node i	

		void readAp(std::ifstream&);
		void readRcab(std::ifstream&);
		void errorMessage(const std::string&) const;
};

#endif
