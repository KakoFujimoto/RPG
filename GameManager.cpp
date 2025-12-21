#include"GameManager.h"
#include"FieldEnemy.h"
#include"DxLib.h"

GameManager::GameManager()
    : ally(
        Position{400, 300},
        AllyParameter("‚Ë‚±", 500, 20, 13, 11, 8, 1, 0)
    ),
    fieldItemManager(),
    itemBag()
{}

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

bool GameManager::checkEncount()
{
    auto& enemies = fieldEnemyManager.getEnemies();

    for (int i = 0; i < static_cast<int>(enemies.size()); ++i)
    {
        auto& e = enemies[i];

        if (!e.getIsActive())
        {
            continue;
        }

        if (hitCheck.check(ally.getPosition(), e.getPosition()))
        {
            e.setIsActive(false);

            currentBattleInfo.enemyName = e.getParameter().getName();
            currentBattleInfo.count = 1;

            isInBattle = true;
            return true;
        }
    }

    return false;
}


FieldEnemyManager& GameManager::getFieldEnemyManager()
{
    return fieldEnemyManager;
}

bool GameManager::isBattle() const
{ 
    return isInBattle;
}
void GameManager::setBattle(bool v)
{ 
    isInBattle = v;
}
void GameManager::update()
{
    if (!isInBattle)
    {
        if (checkEncount())
        {
            isInBattle = true;
        }
    }
}
const BattleStartInfo& GameManager::getBattleInfo() const
{
    return currentBattleInfo;
}
