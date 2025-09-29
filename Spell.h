#pragma once
#include"IHealing.h"
#include"Name.h"

class Spell : public IHealing {
private:
	Name name;
	int mpCost;
	int healAmount;

public:
	Spell(const std::string& n, int cost, int heal)
		: name(n), mpCost(cost), healAmount(heal){ }

};