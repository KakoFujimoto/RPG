#pragma once
#include"EffectType.h"
#include"AllyParameter.h"
#include"RandomGenerator.h"

struct EffectResult;

struct Effect {
    EffectType type;
    int minValue;
    int maxValue;

    EffectResult apply(AllyParameter& target) const;
};
