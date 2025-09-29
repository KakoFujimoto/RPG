#pragma once
#include"RandomGgenerator.h"

class GameManager {
private:
	RandomGenerator rng;
public:
	RandomGenerator getRng() { return rng; }
};