#include "../include/swarm.h"

#include <iostream>

Swarm::Swarm(const Parameter& param) 
	: _param(param)
{
	init(100);
	double trMin = particles.back().getGlobalObj();
	unsigned count = 0;

	while(count <= 500) {
		for(Particle& p : particles) {
			p.move(1,1,2);
		}

		if(trMin == particles.back().getGlobalObj())
			++count;
		else {

			trMin = particles.back().getGlobalObj();
			count = 0;
		}

		//std::cout << trMin << std::endl;
	}

	best_solution = trMin;
}

Swarm::Swarm(const Parameter& param, int iterNumber) 
	: _param(param), _iterationNumber(iterNumber)
{
	
}

void Swarm::init(const int particleNum) {
	for(int i = 0; i < particleNum ; ++i) {
		particles.push_back(Particle(_param));
	}	
}






