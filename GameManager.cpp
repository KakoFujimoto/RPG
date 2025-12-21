#include"GameManager.h"
#include"FieldEnemy.h"
#include"DxLib.h"

GameManager::GameManager()
    : ally(
        Position{400, 300},
        AllyParameter("ねこ", 500, 20, 13, 11, 8, 1, 0)
    ),
    fieldItemManager(),
    itemBag(){}

void GameManager::updateItemBag()
{   
    auto& items = fieldItemManager.getItems();

    for (auto& fieldItem : items)
    {
        if (!fieldItem.getIsActive())
        {
            continue;
        }

        if (hitCheck.check(ally.getPosition(), fieldItem.getPosition()))
        {
            fieldItem.setGotten();
            itemBag.add(fieldItem.getItemData());
        }
    }
}

ItemBag& GameManager::getItemBag()
{
    return itemBag;
}

FieldItemManager& GameManager::getFieldItemManager()
{
    return fieldItemManager;
}

FieldAlly& GameManager::getAlly()
{ 
    return ally;
}

void GameManager::checkEncount()
{
    auto& enemies = fieldEnemyMamager.getEnemies();

    for (auto& e : enemies)
    {
        if (!e.getIsActive())
        {
            continue;
        }

        if (hitCheck.check(ally.getPosition(), e.getPosition()))
        {
            DrawString(20, 440, "敵とエンカウント！", GetColor(255, 255, 255));
            return;
        }
    }
}

FieldEnemyManager& GameManager::getFieldEnemyManager()
{
    return fieldEnemyMamager;
}