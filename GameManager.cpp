#include"GameManager.h"

GameManager::GameManager() {}

bool GameManager::HitCheck(const Position& allyPosition, const Position& object)
{
    int dx = allyPosition.getX() - object.getX();
    int dy = allyPosition.getY() - object.getY();
    float distance = std::sqrt(dx * dx + dy * dy);

    return (distance < 10.0f);
}
void GameManager::updateItemBag()
{
            if (fieldItem.getIsActive() && HitCheck(ally.getPosition(), fieldItem.getPosition())) {
                fieldItem.isGotten();
                itemBag.add(fieldItem.getItemData());
            }
}
ItemBag& GameManager::getItemBag()
{
    return itemBag;
}