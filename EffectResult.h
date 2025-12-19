#pragma once
#include<string>

enum class ActionType {
    Item,
    Spell
};

struct EffectResult
{
    int hpDelta = 0;
    int mpDelta = 0;
    bool success = false;
    ActionType actionType;
    std::string userName;
    std::string actionName;
    //std::string itemName;
    bool mpShortage = false;
};