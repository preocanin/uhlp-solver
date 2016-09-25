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
	: _param(param), current_solution(param.getN()*2,-1)
{
	vmax = 1.0;
	vmin = 0.0;

	//Init solution
	randInitSolution();

	//Local best is a current solution
	std::copy(current_solution.begin(),current_solution.end(),
			std::back_inserter(local_best));

	//Local best objective is equal to current objective
	objectiveCurrent = calculateObjectiveFn();
	objectiveLocalMin = objectiveCurrent;

	//Generating velocity vector
	for(int i = 0; i < param.getN() ; ++i) {
		//int sign= std::rand()%2;
		int v = std::rand()/(1.0*INT_MAX);
		vector_speed.push_back(v);
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
	int n = _param.getN();

	std::vector<int> newSolution(2*n,-1);
	std::vector<double>newVSpeed(n);

	double fl,fg,u;
	double vtr;

	auto sigmd = [](double v) -> double {return 1.0/(1.0+exp(-v));};

	std::set<int> hubs;
	bool indicator = true;
	while(indicator) {	
		hubs.clear();

	for(int i = 0; i < n ; ++i) {
		fl = std::rand()/(1.0*INT_MAX);
		fg = std::rand()/(1.0*INT_MAX);
	
		vtr = vel*vector_speed[i] +
			  ul*(local_best[i] - current_solution[i]) +
			  ug*(global_best[i] - current_solution[i]);

		vtr = vtr > vmax? vmax : vtr;
	    vtr = vtr < vmin? vmin : vtr;

		newVSpeed[i] = vtr;

		u = std::rand()/(1.0*INT_MAX);
		if(u > sigmd(vtr)) {
			newSolution[i] = 0;	
		} else {
			newSolution[i] = 1;
			indicator = false;	
			hubs.insert(i);	
		}
	}
	}

	for(const int i : hubs)
		newSolution[n+i] = i;
	
	std::vector<int> vhubs(hubs.begin(),hubs.end());

	unsigned vsize = vhubs.size();

	for(int i = 0; i < n ; ++i) {
		if(newSolution[n+i] == -1) {
			int hrand = std::rand()%vsize;
			newSolution[n+i] = vhubs[hrand];
		}
	}

	vector_speed = newVSpeed;
	current_solution = newSolution;

	objectiveCurrent = calculateObjectiveFn();

	//New solution to history
	if(all_solutions.find(current_solution) == all_solutions.end())
		all_solutions[current_solution] = objectiveCurrent;

	if(objectiveCurrent < objectiveLocalMin)
		local_best = current_solution;

	if(objectiveCurrent < objectiveGlobal)
		global_best = current_solution;	

//	for (int i = 0; i < n*2; ++i) {
//		std::cout << current_solution[i] << " ";
//		if(i == n-1)
//			std::cout << " | ";	
//	}
//	std::cout << std::endl;
	

}

double Particle::calculateObjectiveFn() const {
	double sumFcost = 0.0;
	int n = _param.getN();	

	auto iter = all_solutions.find(current_solution);
	if(iter != all_solutions.end())
		return  (*iter).second;

	// sum fi*yi, for all i 	
	for(int i = 0; i < n; ++i)
		if(current_solution[i] == 1)
			sumFcost += _param.getFi(i);

	// Sum of flow cost in case of AP instances
	if(_param.format == FI_AP) 
		return sumFcost+calculateAP();	
	else 
	// Sum of flow cost in case of CAB or RAND instances
		return sumFcost+calculateRCAB();
}

void Particle::randInitSolution() {
	int n = _param.getN();
	std::set<int> locatedHubs;

	bool indicator = true;	

	std::vector<int> trSolution(n*2,-1);
	
	//Init HubArray 
	while(indicator) {
		locatedHubs.clear();
		for(int i = 0; i < n ; ++i) {
			int hub = std::rand() % 2;
			if(hub == 1) {
				trSolution[i] = 1;
				indicator = false;
				locatedHubs.insert(i);
			} else
				trSolution[i] = 0;
		}
	}

	std::vector<int> vLocatedHubs(locatedHubs.begin(),locatedHubs.end());

	for(const auto i : vLocatedHubs)
		trSolution[n+i] = i;

	//Join rest of nodes to hubs
	for(int i = 0; i < n ; ++i) {
		if(trSolution[n+i] == -1) {
			int hub = std::rand()%vLocatedHubs.size();
			trSolution[n+i] = vLocatedHubs[hub];
		}
	}	

	current_solution = trSolution;
}

double Particle::calculateAP() const {
	int n = _param.getN();
	double alpha = _param.getAlpha();
	double c = _param.getC();
	double d = _param.getD();
	double sumFlowCost = 0.0;

	for (int i = 0; i < n ; ++i) 
		for (int j = 0;  j < n ; ++j)  {
			if(i!=j) {
				//(c*cik+alpha*ckm+d*cmj)*wij
				double cik,ckm,cmj,wij;
				wij = _param.getWij(i,j);
				cik = c*_param.getCij(i,current_solution[n+i])*wij;
				ckm =	alpha *_param.getCij(current_solution[n+i],
						current_solution[n+j])*wij;
				cmj = d*_param.getCij(current_solution[n+j],j)*wij;
				sumFlowCost += cik+ckm+cmj;
			}
		}
	return sumFlowCost;
}

double Particle::calculateRCAB() const {
	int n = _param.getN();
	double alpha = _param.getAlpha();
	double sumFlowCost = 0.0;
	
	for(int i = 0; i < n ; ++i)
		for(int j = 0; j < n ; ++j) {
			if(i != j) {
				//(cik+ckm+cmj)*wij + (cjm+cmk+cki)*wji
				double cik,ckm,cmj,wij;
				wij = _param.getWij(i,j);
				cik = _param.getCij(i,current_solution[n+i])*wij;
				ckm = _param.getCij(current_solution[n+i],
						current_solution[n+j])*wij*alpha;
				cmj = _param.getCij(current_solution[n+j],j)*wij;
				sumFlowCost +=  (cik + ckm + cmj);
			}
		}
	return sumFlowCost;
}


void Particle::printSolution(std::ostream& out) const {
	int n = _param.getN();
	for (int i = 0; i < n*2; ++i) {
		out << current_solution[i] << " ";
		if(i == n-1)
			out << " | ";	
	}
	out << std::endl;
}
