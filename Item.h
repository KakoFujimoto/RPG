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
	Item(std::string name, const Effect& effect, int amount);
	const std::string& getName() const;
	int getAmount() const;
	const Effect& getEffect() const;
	void decreaseAmount();
};