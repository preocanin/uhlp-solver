#ifndef _SWARM

#define _SWARM

#include "parameter.h"
#include "particle.h"
#include <vector>
#include <utility>

class Swarm {
	public:

		Swarm(const Parameter&);
		Swarm(const Parameter&, int);

		~Swarm() {}

	private:
		const Parameter& _param;	
		int _iterationNumber;
		std::vector<Particle> particles;
};

#endif
