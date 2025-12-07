#include"FieldItemManager.h"

void FieldItemManager::spawn(const Item& item, int maxX, int maxY, RandomGenerator& rng)
{
	FieldItem fi;
	fi.spawn(item, maxX, maxY, rng);
	fieldItems.push_back(fi);
}

void FieldItemManager::draw() const
{
	for (const auto& fi : fieldItems)
	{
		fi.draw();
	}
}

std::vector<FieldItem>& FieldItemManager::getItems()
{
	return fieldItems;
}