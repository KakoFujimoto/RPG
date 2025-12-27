#pragma once
#include "AllyParameter.h"
#include "EnemyParameter.h"

class BattleDamageCalculator {
public:
    // 本来AllyとEnemyの上位概念を設ければメソッドを分ける必要はない
    // 期限の関係で、冗長だがメソッド分化を採った
    static int calcAllyNormalAttack(
        const AllyParameter& attacker,
        const EnemyParameter& defender
    );
    static int calcEnemyNormalAttack(
        const EnemyParameter& attacker,
        const AllyParameter& defender
    );
};