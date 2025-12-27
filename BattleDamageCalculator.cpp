#include "BattleDamageCalculator.h"
#include <algorithm>

int BattleDamageCalculator::calcAllyNormalAttack(
    const AllyParameter& attacker,
    const EnemyParameter& defender
) {
    int atk = attacker.getAttack();
    int def = defender.getDefense();

    int damage = atk - def / 2;

    if (damage < 1) {
        damage = 1;
    }

    return damage;
}
int BattleDamageCalculator::calcEnemyNormalAttack(
    const EnemyParameter& attacker,
    const AllyParameter& defender
) {
    int atk = attacker.getAttack();
    int def = defender.getDefense();

    int damage = atk - def / 2;

    if (damage < 1) {
        damage = 1;
    }

    return damage;
}
