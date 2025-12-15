#pragma once
#include <string>
#include"Effect.h"

class Item {
private:
	std::string name;
	Effect effect;
	int amount;
public:
	Item();
	Item(std::string name, EffectType effectType, int amount);
	std::string getName() const;
	int getAmount() const;
	Effect getEffect();
};