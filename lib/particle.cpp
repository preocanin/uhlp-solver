#include "../include/particle.h"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <map>

double Particle::objectiveGlobal = 0.0;
std::vector<int> Particle::global_best;
std::map<std::vector<int>,double> Particle::all_solutions;

Particle::Particle(const Parameter& param) 
	: _param(param), current_solution(param.getN(),-1)
{
	vmax = param.getN() - 1;
	vmin = -vmax;

	//Generating current solution
	for(unsigned i = 0; i <  current_solution.size() ; ++i) {
		if(current_solution[i] == -1) {
			int nodeHub = std::rand() % param.getN();
			current_solution[i] = nodeHub;
			current_solution[nodeHub] = nodeHub;	
		}		
	}

	//Local best is a current solution
	std::copy(current_solution.begin(),current_solution.end(),
			std::back_inserter(local_best));

	//Local best objective is equal to current objective
	objectiveCurrent = calculateObjectiveFn();
	objectiveLocalMin = objectiveCurrent;

	//Generating velocity vector
	for(int i = 0; i < param.getN() ; ++i) {
		int zero = std::rand()%2;
		int v = std::rand()%param.getN();
		vector_speed.push_back((-1)*zero == 0?v:-v);
	}

	//Updating the global best solution and his objective
	if(global_best.size() == 0) {
		global_best = current_solution;
		objectiveGlobal = objectiveCurrent;
	} else {
		if(objectiveGlobal < objectiveCurrent) {
			global_best = current_solution;
			objectiveGlobal = objectiveCurrent;
		}
	}

	//Add current solution to Map
	if(all_solutions.find(current_solution) == all_solutions.end())
		all_solutions[current_solution] = objectiveCurrent;

}

void Particle::move(const double& ul, const double& ug, const double& vel) {
	
	for(unsigned i = 0; i < current_solution.size() ; ++i) {
		double fl = std::rand()/(1.0*INT_MAX);
		double fg = std::rand()/(1.0*INT_MAX);
	
		double vtr = vel*vector_speed[i] +
		   			 ul*fl*(local_best[i] - current_solution[i]) +
				     ug*fg*(global_best[i] - current_solution[i]);

		vtr = vtr > vmax? vmax : vtr;
		vtr = vtr < vmin? vmin : vtr;
   		
		double sigmd = (vtr <= 0? vtr/(1.0*vmin) : vtr/(1.0*vmax));
		double u = std::rand()/(1.0*INT_MAX);

		if(u > sigmd) {
			vtr = ceil(vtr);	
	
		} else {
			vtr = floor(vtr);	
		}
					
	}
}

double Particle::calculateObjectiveFn() const {
	double sumFcost = 0.0, sumFlowCost=0.0;
	double alpha = _param.getAlpha();
	std::set<int> setOfHubs(current_solution.begin(),current_solution.end());
    
	// sum fi*yi, for all i 	
	for(const unsigned& i : setOfHubs)
		sumFcost += _param.getFi(i);

	// Sum of flow cost in case of AP instances
	if(_param.format == FI_AP) {
		double c = _param.getC();
		double d = _param.getD();

		for (int i = 0; i < _param.getN() ; ++i) 
			for (int j = 0;  j < _param.getN() ; ++j)  {
				if(i!=j) {
					//(c*cik+alpha*ckm+d*cmj)*wij
					double cik,ckm,cmj,wij;
					wij = _param.getWij(i,j);
					cik = c*_param.getCij(i,current_solution[i])*wij;
					ckm =	alpha *_param.getCij(current_solution[i],
							current_solution[j])*wij;
					cmj = d*_param.getCij(current_solution[j],j)*wij;
					sumFlowCost += cik+ckm+cmj;
				}

			}
	} else {
	// Sum of flow cost in case of CAB or RAND instances
		for(int i = 0; i < _param.getN() ; ++i)
			for(int j = i; j < _param.getN() ; ++j) {
				if(i != j) {
					//(cik+ckm+cmj)*wij + (cjm+cmk+cki)*wji
					double cik,ckm,cmj,wij;
					wij = _param.getWij(i,j);
					cik = _param.getCij(i,current_solution[i])*wij;
					ckm = _param.getCij(current_solution[i],
							current_solution[j])*wij*alpha;
					cmj = _param.getCij(current_solution[j],j)*wij;
					sumFlowCost += 2 * (cik + ckm + cmj);
				}
			}
	}

	return sumFlowCost+sumFcost;
}


