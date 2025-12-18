#include "Effect.h"
#include"EffectResult.h"

EffectResult Effect::apply(AllyParameter& target) const
{
    static RandomGenerator rng;
    int value = rng.getRandomValue(minValue, maxValue);

    EffectResult result{};

    switch (type)
    {
    case EffectType::HealHp:
    {
        int before = target.getHp();
        target.healHp(value);
        result.hpDelta = target.getHp() - before;
        break;
    }
    case EffectType::HealMp:
    {
        int before = target.getMp();
        target.healMp(value);
        result.mpDelta = target.getMp() - before;
        break;
    }
    case EffectType::Damage:
    {
        int before = target.getHp();
        target.takeDamage(value);
        result.hpDelta = target.getHp() - before;
        break;
    }
    default:
        result.success = false;
        break;
    }

    result.success = true;

    return result;
}
