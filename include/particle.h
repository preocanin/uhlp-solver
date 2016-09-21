#ifndef _PARTICLE

#define _PARTICLE

#include "parameter.h"
#include <vector>

class Particle {
	public:
		Particle(const Parameter&,std::vector<int>&);

		bool isEmpty() const {
			return current_solution == std::vector<int>(_param.getN(),-1); 
		}

		bool operator== (const Particle& p) const {
			return current_solution == p.current_solution;
		}

		bool operator< (const Particle& p) const {
			return objectiveCurrent < p.objectiveCurrent;
		}

		bool operator> (const Particle& p) const {
			return objectiveCurrent > p.objectiveCurrent;
		}
	
			

		~Particle() {}
		
	private:
		const Parameter& _param;

		double objectiveCurrent;
		double objectiveLocalMin;

		std::vector<int> current_solution;
		std::vector<int> local_best;
		std::vector<int> &global_best;
		std::vector<int> vector_speed;

		double calculateObjectiveFn() const;
		double calculateFlowCost(const int i,const int j) const {
			return _param.getCij(i,j)*_param.getWij(i,j); 
		}
};

#endif
