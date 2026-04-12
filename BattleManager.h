#pragma once
#include"Command.h"
#include"FieldEnemy.h"
#include"FieldAlly.h"

class GameManager;
class BattleManager
{
public:
    BattleManager(GameManager* gm);
    void submitPlayerCommand(const Command& playerCommand);
    void requestEnemyTurnAction();
    bool isEnemyTurn() const;
    void notifyAllyActionFinished();
    void startRunAway();
    void update();
    bool isRunningAway() const;
    bool consumeSkipInput();
    void reset();

private:
    enum class BattlePhase
    {
        StartDelay,
        AllyTurn,
        EnemyTurn,
        Escape,
        WinMessage
    };

    int battleRunStartTime = 0;
    bool isGuarding = false;
    bool skipInputPending = false;
    bool enemyTurnActionRequested = false;

    bool isEnemyDead() const;
    bool isAllyDead() const;
    void executeAllyAction(const Command& cmd);
    void executeEnemyAction();
    void onWin();
    void onLose();

    GameManager* gameManager;
    BattlePhase phase = BattlePhase::AllyTurn;
};