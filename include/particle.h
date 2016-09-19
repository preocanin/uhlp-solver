#ifndef _PARTICLE

#define _PARTICLE

#include "parameter.h"

class Particle {
	public:
		Particle(const Parameter& param) : _param(param) {}

		~Particle() {}
		
	private:
		const Parameter& _param;
};

#endif
