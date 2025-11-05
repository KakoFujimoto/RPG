#include"GameManager.h"

GameManager::GameManager()
    : ally("‚Ë‚±", 400, 300),
    fieldItem(),
    itemBag(){}

void GameManager::updateItemBag()
{
            if (fieldItem.getIsActive() && hitCheck.check(ally.getPosition(), fieldItem.getPosition())) {
                fieldItem.setGotten();
                itemBag.add(fieldItem.getItemData());
            }
}
ItemBag& GameManager::getItemBag()
{
    return itemBag;
}