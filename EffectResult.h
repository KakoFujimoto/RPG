#pragma once
#include<string>

struct EffectResult
{
    int hpDelta = 0;
    int mpDelta = 0;
    bool success = false;

    std::string userName;
    std::string itemName;
};