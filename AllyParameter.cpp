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
(std::string n, int h, int m,
    int atk, int def, int spd,
    int lvl, int exp)
    : name(n), hp(h), mp(m),
    attackPower(atk), defensePower(def), speed(spd),
    level(lvl), gainedExp(exp)
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
    return { name, hp, mp, level };
}