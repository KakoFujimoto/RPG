#pragma once
#include <string>

struct Effect;
class RandomGenerator;
class Spell {
private:
	RandomGenerator& rng;
	std::string name;
	Effect& effect;
	int mpCost;
	bool isLearnd = false;

public:
	Spell(RandomGenerator& rng, const std::string n, int cost, Effect& effect);
	const std::string& getName() const;
	int getMpCost() const;
	bool getIsLearned() const;
	void learn();
	Effect& getEffect() const;
};