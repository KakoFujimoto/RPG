#include "BattleManager.h"
#include "BattleDamageCalculator.h"
#include "GameManager.h"

BattleManager::BattleManager(GameManager* gm)
    : gameManager(gm)
{
}

void BattleManager::executeRound(const Command& playerCommand)
{
    // 味方の行動（現在は、味方→敵の行動順は固定）
    if (phase == BattlePhase::AllyTurn)
    {
        executeAllyAction(playerCommand);

        if (isEnemyDead())
        {
            onWin();
            return;
        }

        // 敵ターン
        phase = BattlePhase::EnemyTurn;
        return;
    }

    if (phase == BattlePhase::EnemyTurn)
    {
        executeEnemyAction();

        if (isAllyDead())
        {
            onLose();
            return;
        }

        // 次は味方ターン
        phase = BattlePhase::AllyTurn;
        return;
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

    if (cmd.type == Command::Type::Attack)
    {
        int damage = BattleDamageCalculator::calcAllyNormalAttack(
            ally.getParameter(),
            enemy.getParameter()
        );

        enemy.getParameter().takeDamage(damage);

        gameManager->getBattleWindowRenderer().setMessage(
            ally.getName() + "の こうげき！\n" +
            enemy.getName() + "に " +
            std::to_string(damage) + "の ダメージ!"
        );
    }

    // じゅもん・ぼうぎょは後で
}

void BattleManager::executeEnemyAction()
{
    auto& ally = gameManager->getAlly();
    auto& enemy = gameManager->getEnemy();

    int damage = BattleDamageCalculator::calcEnemyNormalAttack(
        enemy.getParameter(),
        ally.getParameter()
    );

    ally.getParameter().takeDamage(damage);

    gameManager->getBattleWindowRenderer().setMessage(
        enemy.getName() + "の こうげき!\n" +
        ally.getName() + "に " +
        std::to_string(damage) + "の ダメージ！"
    );
}

void BattleManager::onWin()
{
    phase = BattlePhase::AllyTurn;

    auto& ally = gameManager->getAlly();
    auto& enemy = gameManager->getEnemy();

    int exp = enemy.getParameter().getExp();

    ally.getParameter().addExp(exp);

    gameManager->getBattleWindowRenderer().setMessage(
        enemy.getName() + "を たおした！\n" +
        std::to_string(exp) + "の けいけんちを かくとく!"
    );

    gameManager->endBattle();
}

void BattleManager::onLose()
{
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