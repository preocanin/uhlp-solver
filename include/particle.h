#ifndef _PARTICLE

#define _PARTICLE

#include "parameter.h"
#include <vector>
#include <map>

class Particle {
	public:
		Particle(const Parameter&);

		void move(const double&,const double&,const double&);

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

		double getGlobalObj() const { return objectiveGlobal; }	
		double getObj() const { return objectiveCurrent; }			

	 	void printSolution(std::ostream& out) const;

		~Particle() {}
		
	private:
		const Parameter& _param;

		double objectiveCurrent;
		double objectiveLocalMin;

		double vmax,vmin;

		std::vector<int> current_solution;
		std::vector<int> local_best;
		std::vector<double> vector_speed;

		static double objectiveGlobal;
		static std::vector<int> global_best;
		static std::map<std::vector<int>,double> all_solutions;

		double calculateObjectiveFn() const;
		double calculateAP() const;
		double calculateRCAB() const;
		void randInitSolution();
};


#endif
