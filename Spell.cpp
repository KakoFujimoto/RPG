#include"Spell.h"
#include"Effect.h"

Spell::Spell(RandomGenerator& rng,
	const std::string n,
	int cost,
	Effect& effect)
		: rng(rng), name(n), mpCost(cost) ,effect(effect) { }

const std::string& Spell::getName() const
{
	return name;
}

int Spell::getMpCost() const
{
	return mpCost;
}

bool Spell::getIsLearned() const
{
	return isLearnd;
}

void Spell::learn()
{
	isLearnd = true;
}

Effect& Spell::getEffect() const
{
	return effect;
}