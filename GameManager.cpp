#include"GameManager.h"
#include"FieldEnemy.h"
#include"DxLib.h"

GameManager::GameManager(Display& display)
    : ally(
        Position{400, 300},
        AllyParameter("ねこ", 500, 20, 13, 11, 8, 1, 0)
    ),
    fieldItemManager(),
    itemBag(),
    battleWindowRenderer(display)
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
void GameManager::endBattle()
{
    isInBattle = false;
}
int GameManager::getBattleMenuCount() const
{
    return battleWindowRenderer.getMenuCount();
}

BattleWindowRenderer& GameManager::getBattleWindowRenderer()
{
    return battleWindowRenderer;
}
void BattleWindowRenderer::setSelectedMenuIndex(int index)
{
    // メニューが無いなら何もしない
    int count = static_cast<int>(battleMenuItems.size());
    if (count <= 0) {
        selectedMenuIndex = 0;
        return;
    }

    // 範囲外なら丸める（clamp）
    if (index < 0) {
        index = 0;
    }
    else if (index >= count) {
        index = count - 1;
    }

    selectedMenuIndex = index;
}