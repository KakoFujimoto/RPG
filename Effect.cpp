#include "Effect.h"
#include"EffectResult.h"

EffectResult Effect::apply(AllyParameter& target) const
{
    static RandomGenerator rng;
    int value = rng.getRandomValue(minValue, maxValue);

    EffectResult result{};
    result.success = true;
    result.mpShortage = false;

    switch (type)
    {
    case EffectType::HealHp:
    {
        result.hpDelta = target.healHp(value);
        break;
    }
    case EffectType::HealMp:
    {
        result.mpDelta = target.healMp(value);
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
    return result;
}
