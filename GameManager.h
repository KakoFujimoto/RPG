#pragma once
#include"RandomGenerator.h"

class GameManager {
private:
	RandomGenerator rng;
public:
	RandomGenerator getRng() { return rng; }
};