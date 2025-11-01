#pragma once
#include <string>

class Item {
private:
	std::string name;
	//std::string kind;
	int amount;
public:
	Item();
	Item(std::string name, int amount);
	std::string getName() const;
	int getAmount() const;
};