#include "Item.h"

Item::Item()
	: name(""), amount(0) {

}
Item::Item(std::string name, int amount)
	:name(name), amount(amount){ }

std::string Item::getName() const
{
	return name;
}

int Item::getAmount() const
{
	return amount;
}

Effect Item::getEffect()
{
	return effect;
}