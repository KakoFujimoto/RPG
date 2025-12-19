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
        int healed = target.healHp(value);
        result.hpDelta = healed;
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
    return result;
}
