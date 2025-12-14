#include "Effect.h"

void Effect::apply(AllyParameter& target) const {
    static RandomGenerator rng;

    int value = rng.getRandomValue(minValue, maxValue);

    switch (type) {
    case EffectType::HealHp:
        target.healHp(value);
        break;
    case EffectType::HealMp:
        target.healMp(value);
        break;
    case EffectType::Damage:
        target.takeDamage(value);
        break;
    }
}