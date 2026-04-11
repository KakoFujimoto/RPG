#include"BattleManager.h"
#include"BattleDamageCalculator.h"
#include"GameManager.h"
#include"EffectResult.h"
#include"BattleMessageBuilder.h"
#include<WIndows.h>
#include<DxLib.h>

BattleManager::BattleManager(GameManager* gm)
    : gameManager(gm)
{
}

void BattleManager::submitPlayerCommand(const Command& playerCommand)
{
    if (phase != BattlePhase::AllyTurn)
    {
        return;
    }

    executeAllyAction(playerCommand);

    if (isEnemyDead())
    {
        onWin();
        return;
    }

    phase = BattlePhase::EnemyTurn;
}

void BattleManager::requestEnemyTurnAction()
{
    if (phase == BattlePhase::EnemyTurn)
    {
        enemyTurnActionRequested = true;
    }
}

bool BattleManager::isEnemyDead() const
{
    return gameManager->getEnemy().getParameter().getHp() <= 0;
}

bool BattleManager::isAllyDead() const
{
    return gameManager->getAlly().getParameter().getHp() <= 0;
}

void BattleManager::executeAllyAction(const Command& cmd)
{
    auto& ally = gameManager->getAlly();
    auto& enemy = gameManager->getEnemy();

    switch (cmd.type)
    {
    case Command::Type::Attack:
    {
        int damage = BattleDamageCalculator::calcAllyNormalAttack(
            ally.getParameter(),
            enemy.getParameter()
        );

        enemy.getParameter().takeDamage(damage);

        gameManager->getBattleWindowRenderer().setMessage(
            ally.getName() + "の こうげき！\n" +
            enemy.getName() + "に " +
            std::to_string(damage) + "の ダメージ！"
        );
        break;
    }

    case Command::Type::Spell:
    {
        EffectResult result =
            ally.getParameter()
            .getSpellManager()
            .castSpell(cmd.spellName, ally);

        std::string msg = BattleMessageBuilder::build(result);
        gameManager->getBattleWindowRenderer().setMessage(msg);
        break;
    }

    case Command::Type::Guard:
    {
        isGuarding = true;
        gameManager->getBattleWindowRenderer().setMessage(
            ally.getName() + "は みをまもっている！"
        );
        break;
    }

    case Command::Type::Item:
    {
        break;
    }
    }
}

void BattleManager::executeEnemyAction()
{
    auto& ally = gameManager->getAlly();
    auto& enemy = gameManager->getEnemy();

    int damage = BattleDamageCalculator::calcEnemyNormalAttack(
        enemy.getParameter(),
        ally.getParameter()
    );

    if (isGuarding)
    {
        damage /= 2;
        isGuarding = false;
    }

    ally.getParameter().takeDamage(damage);

    gameManager->getBattleWindowRenderer().setMessage(
        enemy.getName() + "の こうげき!\n" +
        ally.getName() + "に " +
        std::to_string(damage) + "の ダメージ！"
    );
}

void BattleManager::onWin()
{
    OutputDebugStringA("[DEBUG] onWin called\n");

    auto& ally = gameManager->getAlly();
    auto& enemy = gameManager->getEnemy();

    int exp = enemy.getParameter().getExp();
    ally.getParameter().addExp(exp);

    gameManager->getBattleWindowRenderer().setMessage(
        enemy.getName() + "を たおした！\n" +
        std::to_string(exp) + "の けいけんちを かくとく!\n"
        + "画面を閉じてください\n"
    );

    phase = BattlePhase::WinMessage;
}

void BattleManager::onLose()
{
    OutputDebugStringA("[DEBUG] onLose called\n");

    phase = BattlePhase::AllyTurn;

    gameManager->getBattleWindowRenderer().setMessage(
        "しんでしまった…画面を閉じてください"
    );
    gameManager->setGameOver();
}

bool BattleManager::isEnemyTurn() const
{
    return phase == BattlePhase::EnemyTurn;
}

void BattleManager::notifyAllyActionFinished()
{
    if (phase == BattlePhase::AllyTurn)
    {
        phase = BattlePhase::EnemyTurn;
    }
}

void BattleManager::startRunAway()
{
    phase = BattlePhase::Escape;
    battleRunStartTime = GetNowCount();
}

void BattleManager::update()
{
    bool nowBattle = gameManager->isBattle();
    battleStartedThisFrame = (nowBattle && !prevIsBattle);

    if (battleStartedThisFrame)
    {
        phase = BattlePhase::StartDelay;
        skipInputPending = true;
        enemyTurnActionRequested = false;
        isGuarding = false;
    }
    prevIsBattle = nowBattle;

    if (phase == BattlePhase::StartDelay)
    {
        phase = BattlePhase::AllyTurn;
    }

    if (phase == BattlePhase::EnemyTurn && enemyTurnActionRequested)
    {
        enemyTurnActionRequested = false;
        executeEnemyAction();

        if (isAllyDead())
        {
            onLose();
            return;
        }

        phase = BattlePhase::AllyTurn;
        gameManager->onBattleAllyTurnStart();
        return;
    }

    if (phase == BattlePhase::Escape)
    {
        if (GetNowCount() - battleRunStartTime > 1200)
        {
            gameManager->endBattle();
            phase = BattlePhase::AllyTurn;
        }
    }
}

bool BattleManager::isRunningAway() const
{
    return phase == BattlePhase::Escape;
}

bool BattleManager::isBattleStarted() const
{
    return battleStartedThisFrame;
}

bool BattleManager::consumeSkipInput()
{
    if (skipInputPending)
    {
        skipInputPending = false;
        return true;
    }
    return false;
}

void BattleManager::reset()
{
    phase = BattlePhase::AllyTurn;
    battleRunStartTime = 0;
    isGuarding = false;
    battleStartedThisFrame = false;
    skipInputPending = false;
    enemyTurnActionRequested = false;
    prevIsBattle = false;
}