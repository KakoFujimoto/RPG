#include "AllyParameter.h"

AllyParameter::AllyParameter()
    : name(""),
    hp(0),
    mp(0),
    attackPower(0),
    defensePower(0),
    speed(0),
    level(1),
    gainedExp(0)
{
}

AllyParameter::AllyParameter
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
    gainedExp(exp)
{
}

SpellManager& AllyParameter::getSpellManager()
{
    return spellManager;
}

const SpellManager& AllyParameter::getSpellManager() const
{
    return spellManager;
}

AllyParameter::AllyStatusView AllyParameter::getStatusView() const
{
    return { 
        name,
        hp,
        maxHp,
        mp,
        maxMp,
        level
    };
}
void AllyParameter::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}

void AllyParameter::healHp(int amount)
{
    hp += amount;
    if (hp > maxHp)
    {
        hp = maxHp;
    }
}

void AllyParameter::consumeMp(int amount)
{
    mp -= amount;
    if (mp < 0)
    {
        mp = 0;
    }
}

void AllyParameter::healMp(int amount)
{
    mp += amount;
    if (mp > maxMp)
    {
        mp = maxMp;
    }
}

int AllyParameter::getHp()
{
    return hp;
}

int AllyParameter::getMp()
{
    return mp;
}