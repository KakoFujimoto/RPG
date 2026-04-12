#pragma once
#include <algorithm>

class BattleDamageCalculator {
public:
    template <typename Attacker, typename Defender>
    static int calcNormalAttack(
        const Attacker& attacker,
        const Defender& defender
    )
    {
        int atk = attacker.getAttack();
        int def = defender.getDefense();

        return std::max(1, atk - def / 2);
    }
};