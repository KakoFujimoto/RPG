#pragma once
#include <string>

class RandomGenerator;
class Spell {
private:
	RandomGenerator& rng;
	std::string name;
	int mpCost;
	bool isLearnd = false;

public:
	Spell(RandomGenerator& rng, const std::string n, int cost);
	const std::string& getName() const;
	int getMpCost() const;
	bool getIsLearned() const;
	void learn();
};