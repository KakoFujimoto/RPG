#pragma once
#include <vector>
#include "FieldItem.h"

class FieldItemManager {
private:
	std::vector<FieldItem> fieldItems;

public:
	void spawn(const Item& newItem, int maxX, int maxY, RandomGenerator& rng);
	void draw() const;
	std::vector<FieldItem>& getItems();
};
