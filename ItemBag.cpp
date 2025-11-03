#include"ItemBag.h"

void ItemBag::add(const Item& item)
{
	items.push_back(item);
}
std::vector<Item>& ItemBag::getItems()
{
	return items;
}