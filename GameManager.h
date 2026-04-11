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
#include"Input.h"
#include <memory>


class Display;
class IGameState;
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
    ~GameManager();
    void update();
    void draw();
    void changeState(GameState newState);
    void requestStateChange(GameState newState);
    void applyStateChange();
    void updateItemBag();
    ItemBag& getItemBag();
    FieldItemManager& getFieldItemManager();
    FieldEnemyManager& getFieldEnemyManager();
    FieldAlly& getAlly();
    FieldEnemy& getEnemy();
    Input& getInput();
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
    Display& getDisplay();
    // デバッグ用
    int getDebugBattleEnemyHp();
    void onBattleAllyTurnStart();
    bool getCanShow();

private:
    Display& display;
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
    GameState nextState = GameState::Playing;
    bool hasStateChangeRequest = false;
    std::unique_ptr<IGameState> currentState;
    BattleManager battleManager;
    Input input;
    // デバッグ用
    int debugBattleEnemyHp = -1;
    bool canShow = false;
};