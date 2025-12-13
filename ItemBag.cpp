#include"ItemBag.h"

void ItemBag::add(const Item& item)
{
	items.push_back(item);
}
const std::vector<Item>& ItemBag::getItems() const
{
	return items;
}