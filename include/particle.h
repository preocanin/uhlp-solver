#ifndef _PARTICLE

#define _PARTICLE

#include "parameter.h"
#include <vector>

class Particle {
	public:
		Particle(const Parameter& param) 
			: _param(param), _solution(param.getN(),-1) {}

		~Particle() {}
		
	private:
		const Parameter& _param;
		std::vector<int> _solution;
};

#endif
