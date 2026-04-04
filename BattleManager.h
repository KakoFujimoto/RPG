#pragma once
#include"Command.h"
#include"FieldEnemy.h"
#include"FieldAlly.h"

class GameManager;
class BattleManager
{
public:
    BattleManager(GameManager* gm);
    void executeRound(const Command& playerCommand);
    bool isEnemyTurn() const;
    void notifyAllyActionFinished();
    void startRunAway();
    void update();
    bool isRunningAway() const;
    bool isBattleStarted() const;
    bool consumeSkipInputFlag();

private:
    enum class BattlePhase
    {
        AllyTurn,
        EnemyTurn,
        WinMessage
    };

    int battleRunStartTime = 0;
    bool isGuarding = false;
    bool runningAway = false;
    bool isBattleStartedThisFrame = false;
    bool prevIsBattle = false;
    bool shouldSkipInputThisFrame = false;

    bool isEnemyDead() const;
    bool isAllyDead() const;
    void executeAllyAction(const Command& cmd);
    void executeEnemyAction();
    void onWin();
    void onLose();

    GameManager* gameManager;
    BattlePhase phase = BattlePhase::AllyTurn;
};