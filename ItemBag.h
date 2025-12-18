#pragma once
#include <vector>
#include "Item.h"

class FieldAlly;
class EffectResult;

class ItemBag {
private:
	std::vector<Item> items;
public:
	void add(const Item& item);
	std::vector<Item>::iterator find(const std::string& itemName);
	const std::vector<Item>& getItems() const;
	EffectResult useItem(const std::string& itemName, FieldAlly& ally);
	};