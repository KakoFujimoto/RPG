#pragma once
#include"Position.h"
#include"FieldItem.h"
#include"FieldItemManager.h"
#include"FieldAlly.h"
#include"FieldEnemy.h"
#include"ItemBag.h"
#include"HitCheck.h"
#include"FieldEnemyManager.h"
#include"BattleStartInfo.h"
#include"BattleWindowRenderer.h"
#include"BattleManager.h"


class Display;
class GameManager
{
public:
    enum class GameState
    {
        Playing,
        Battle,
        GameOver
    };
    GameManager(Display& display);
    void update();
    void updateItemBag();
    ItemBag& getItemBag();
    FieldItemManager& getFieldItemManager();
    FieldEnemyManager& getFieldEnemyManager();
    FieldAlly& getAlly();
    FieldEnemy& getEnemy();
    bool checkEncount();
    bool isBattle() const;
    void startBattle(const BattleStartInfo& info);
    void endBattle();
    const BattleStartInfo& getBattleInfo() const;
    int getBattleMenuCount() const;
    BattleWindowRenderer& getBattleWindowRenderer();
    void setGameOver();
    bool isGameOver() const;
    GameState getState() const;
    BattleManager& getBattleManager();
    // デバッグ用
    int getDebugBattleEnemyHp();

private:
    FieldAlly ally;
    FieldEnemy enemy;
    ItemBag itemBag;
    FieldItemManager fieldItemManager;
    FieldEnemyManager fieldEnemyManager;
    HitCheck hitCheck;
    bool isInBattle = false;
    BattleStartInfo currentBattleInfo;
    BattleWindowRenderer battleWindowRenderer;
    GameState state = GameState::Playing;
    BattleManager battleManager;
    // デバッグ用
    int debugBattleEnemyHp = -1;

};