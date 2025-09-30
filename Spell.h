#pragma once
#include"Name.h"

class RandomGenerator;
class Spell {
private:
	RandomGenerator& rng;
	Name name;
	int mpCost;

public:
	Spell(RandomGenerator& rng, const std::string& n, int cost)
		: rng(rng), name(n), mpCost(cost){ }
};