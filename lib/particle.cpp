#include "../include/particle.h"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstdlib>

Particle::Particle(const Parameter& param,std::vector<int>& best) 
	: _param(param), current_solution(param.getN(),-1), global_best(best)
{
	for(unsigned i = 0; i <  current_solution.size() ; ++i) {
		if(current_solution[i] == -1) {
			int nodeHub = std::rand() % param.getN();
			current_solution[i] = nodeHub;
			current_solution[nodeHub] = nodeHub;	
		}		
	}

	std::copy(current_solution.begin(),current_solution.end(),
			std::back_inserter(local_best));

	objectiveCurrent = calculateObjectiveFn();
	objectiveLocalMin = objectiveCurrent;

	for(int i = 0; i < param.getN() ; ++i) {
		int zero = std::rand()%2;
		int v = std::rand()%param.getN();
		vector_speed.push_back((-1)*zero == 0?v:-v);
	}

}

double Particle::calculateObjectiveFn() const {
	double sumFcost = 0.0,sumFlowCost=0.0;
	std::set<int> setOfHubs(current_solution.begin(),current_solution.end());
	for(const unsigned& i : setOfHubs)
		sumFcost += _param.getFi(i);

	if(_param.format == FI_AP) {
		double c = _param.getC();
		double d = _param.getD();
		double cik,ckm,cmj;

		for (int i = 0; i < _param.getN() ; ++i) 
			for (int j = 0;  j < _param.getN() ; ++j)  {
				if(i!=j) {
					cik = c*calculateFlowCost(i,current_solution[i]);
					ckm =	_param.getAlpha() *calculateFlowCost(current_solution[i],
							current_solution[j]);
					cmj = d*calculateFlowCost(current_solution[j],j);
					sumFlowCost += cik+ckm+cmj;
				}

			}
	} else {
		double sumFlowCost = 0.0;
		double c1,c2,c3;

		for(int i = 0; i < _param.getN() ; ++i)
			for(int j = i; j < _param.getN() ; ++j) {
				if(i != j) {
					c1 = calculateFlowCost(i,current_solution[i]);
					c2 = _param.getAlpha()*calculateFlowCost(current_solution[i],
				                           current_solution[j]);
					c3 = calculateFlowCost(current_solution[j],j);			
					sumFlowCost += 2 * (c1 + c2 + c3);
				}
			}
	}
	return sumFlowCost+sumFcost;
}


