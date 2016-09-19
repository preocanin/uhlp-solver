#include "../include/swarm.h"

Swarm::Swarm(const Parameter& param) : _param(param) {}
Swarm::Swarm(const Parameter& param, int iterNumber) 
	: _param(param), _iterationNumber(iterNumber) {}


