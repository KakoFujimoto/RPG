#include"ItemBag.h"
#include"FieldAlly.h"

void ItemBag::add(const Item& item)
{
	items.push_back(item);
}

std::vector<Item>::iterator ItemBag::find(const std::string& itemName)
{
    return std::find_if(
        items.begin(),
        items.end(),
        [&](const Item& item)
        {
            return item.getName() == itemName;
        }
    );
}

const std::vector<Item>& ItemBag::getItems() const
{
	return items;
}

bool ItemBag::useItem(
    const std::string& itemName,
    FieldAlly& ally
)
{
    auto it = find(itemName);

    if (it == items.end() || it->getAmount() <= 0)
    {
        return false;
    }

    ally.useItem(*it);
    it->decreaseAmount();

    return true;
}