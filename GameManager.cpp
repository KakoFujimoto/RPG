#include"GameManager.h"
#include"FieldEnemy.h"
#include"FieldMenu.h"
#include"DxLib.h"

GameManager::GameManager(Display& display)
    : display(display)
    , ally(
        Position{ 400, 300 },
        AllyParameter("ねこ", 500, 20, 13, 11, 8, 1, 0)
    ),
    fieldItemManager(),
    itemBag(),
    battleWindowRenderer(display),
    battleManager(this)
{
    fieldMenu = std::make_unique<FieldMenu>(this, display, ally.getParameter());
}

GameManager::~GameManager() = default;

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

FieldEnemy& GameManager::getEnemy()
{
    return enemy;
}

Input& GameManager::getInput()
{
    return input;
}

bool GameManager::checkEncount()
{
    auto& enemies = fieldEnemyManager.getEnemies();

    for (auto& e : enemies)
    {
        if (!e.getIsActive())
        {
            continue;
        }

        if (hitCheck.check(ally.getPosition(), e.getPosition()))
        {
            e.setIsActive(false);

            BattleStartInfo info;
            info.enemyParam = e.getParameter();
            info.count = 1;

            startBattle(info);
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
void GameManager::update()
{
    input.update();

    switch (state)
    {
    case GameState::Playing:
        updatePlaying();
        break;
    case GameState::Battle:
        updateBattle();
        break;
    case GameState::GameOver:
        updateGameOver();
        break;
    }
}

void GameManager::updatePlaying()
{
    updateItemBag();
    checkEncount();

    fieldMenu->update(input);

    if (!isBattle() && !fieldMenu->getIsOpen())
    {
        ally.move();
    }
}

void GameManager::updateBattle()
{
    battleManager.update();
    // Battle系処理にFieldの処理が入っているのは今後見直す
    fieldMenu->update(input);
}

void GameManager::updateGameOver()
{
    // 現時点では更新処理なし
}

void GameManager::draw()
{
    switch (state)
    {
    case GameState::Playing:
        drawPlaying();
        break;
    case GameState::Battle:
        drawBattle();
        break;
    case GameState::GameOver:
        drawGameOver();
        break;
    }
}

void GameManager::drawPlaying()
{
    int bgColor = GetColor(0, 140, 0);
    DrawBox(0, 0, 800, 600, bgColor, TRUE);

    DrawString(
        ally.getX(),
        ally.getY(),
        ally.getName().c_str(),
        GetColor(255, 255, 255)
    );

    fieldMenu->draw(display);

    DrawFormatString(
        20, 20,
        GetColor(255, 255, 255),
        "[DEBUG]canShowFlg: %d",
        getCanShow()
    );

    fieldEnemyManager.draw();
    fieldItemManager.draw();
}

void GameManager::drawBattle()
{
    int bgColor = GetColor(0, 140, 0);
    DrawBox(0, 0, 800, 600, bgColor, TRUE);

    DrawString(
        ally.getX(),
        ally.getY(),
        ally.getName().c_str(),
        GetColor(255, 255, 255)
    );

    fieldMenu->draw(display);

    DrawFormatString(
        20, 20,
        GetColor(255, 255, 255),
        "[DEBUG]canShowFlg: %d",
        getCanShow()
    );
}

void GameManager::drawGameOver()
{
    if (isBattle())
    {
        drawBattle();
        return;
    }
    drawPlaying();
}



const BattleStartInfo& GameManager::getBattleInfo() const
{
    return currentBattleInfo;
}
void GameManager::endBattle()
{
    isInBattle = false;
    state = GameState::Playing;
    battleWindowRenderer.clearMessage();
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
void GameManager::startBattle(const BattleStartInfo& info)
{
    currentBattleInfo = info;
    isInBattle = true;
    state = GameState::Battle;

    enemy.getParameter() = info.enemyParam;

    battleWindowRenderer.setSelectedMenuIndex(0);
    battleWindowRenderer.clearMessage();
    // アクセサー経由じゃないから良くなさそう
    battleWindowRenderer.canShowBattleStartMessage = true;
    // デバッグ用
    debugBattleEnemyHp = enemy.getParameter().getHp();
    canShow = battleWindowRenderer.canShowBattleStartMessage;
}

void GameManager::setGameOver()
{
    state = GameState::GameOver;
}

bool GameManager::isGameOver() const
{
    return state == GameState::GameOver;
}

GameManager::GameState GameManager::getState() const
{
    return state;
}
BattleManager& GameManager::getBattleManager()
{
    return battleManager;
}
//デバッグ用
int GameManager::getDebugBattleEnemyHp()
{
    return debugBattleEnemyHp;
}
//デバッグ用
bool GameManager::getCanShow()
{
    return canShow;
}
void GameManager::onBattleAllyTurnStart()
{
    battleWindowRenderer.setSelectedMenuIndex(0);
}