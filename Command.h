#pragma once
#include<string>

// プレイヤーが選択した行動を表す
struct Command
{
    enum class Type
    {
        Attack,
        Spell,
        Guard,
        Item
    };

    Type type;
    std::string spellName;
    std::string itemName;

    Command(Type t = Type::Attack)
        : type(t)
    {
    }
};
