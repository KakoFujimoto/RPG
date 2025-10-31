#pragma once
#include <vector>
#include "Item.h"

class ItemBag {
private:
	std::vector<Item> items;
public:
	void add(const Item& item);
	void remove	(const std::string& itemName);
	std::vector<Item>& getItems();
	};