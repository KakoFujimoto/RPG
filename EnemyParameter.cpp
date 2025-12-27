#include"EnemyParameter.h"

EnemyParameter::EnemyParameter()
    : name(""),
    hp(0),
    mp(0),
    maxHp(0),
    maxMp(0),
    attackPower(0),
    defensePower(0),
    speed(0),
    level(1),
    exp(0)
{
}

EnemyParameter::EnemyParameter
(std::string n,
    int maxHp, int maxMp,
    int atk, int def, int spd,
    int lvl, int exp)
    : name(n),
    maxHp(maxHp),
    maxMp(maxMp),
    hp(maxHp),
    mp(maxMp),
    attackPower(atk),
    defensePower(def),
    speed(spd),
    level(lvl),
    exp(exp)
{
}
const std::string EnemyParameter::getName() const
{
    return name;
}
const int EnemyParameter::getAttack() const
{
    return attackPower;
}
const int EnemyParameter::getDefense() const
{
    return defensePower;
}