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

private:
    enum class BattlePhase
    {
        AllyTurn,
        EnemyTurn,
        WinMessage
    };
    bool isEnemyDead() const;
    bool isAllyDead() const;
    void executeAllyAction(const Command& cmd);
    void executeEnemyAction();
    void onWin();
    void onLose();
    GameManager* gameManager;
    BattlePhase phase = BattlePhase::AllyTurn;
    bool isGuarding = false;
};