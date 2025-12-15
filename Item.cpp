#include "Item.h"

Item::Item()
	: name(""), amount(0) {

}
Item::Item(std::string name, const Effect& effect, int amount)
	:name(name), effect(effect), amount(amount){ }

const std::string& Item::getName() const
{
	return name;
}

int Item::getAmount() const
{
	return amount;
}

const Effect& Item::getEffect() const
{
	return effect;
}

void Item::decreaseAmount()
{
	if (amount > 0)
	{
	amount--;
	}
}
