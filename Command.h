#pragma once

// プレイヤーが選択した行動を表す
struct Command
{
    enum class Type
    {
        Attack, // 通常攻撃
        // Spell,
        // Guard,
    };

    Type type;


    Command(Type t = Type::Attack)
        : type(t)
    {
    }
};
