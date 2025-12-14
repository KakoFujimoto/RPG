#pragma once
#include"EffectType.h"
#include"AllyParameter.h"
#include"RandomGenerator.h"

struct Effect {
    EffectType type;
    int minValue;
    int maxValue;

    void apply(AllyParameter& target) const;
};
