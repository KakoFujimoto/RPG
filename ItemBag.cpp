#include"ItemBag.h"
#include"FieldAlly.h"
#include"EffectResult.h"

ItemBag::ItemBag() {}

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

EffectResult ItemBag::useItem(
    const std::string& itemName,
    FieldAlly& ally
)
{
    auto it = find(itemName);

    // ŠŽ‚µ‚Ä‚¢‚È‚¢AŒÂ”0‚Ìê‡
    if (it == items.end() || it->getAmount() <= 0)
    {
        EffectResult result;
        result.success = false;
        result.actionType = ActionType::Item;
        return result;
    }

    EffectResult result = ally.useItem(*it);

    result.actionType = ActionType::Item;
    result.userName = ally.getName();
    result.actionName = it->getName();

    if (result.success)
    {
        it->decreaseAmount();
    }

    return result;
}