#include "AllyParameter.h"
#include "EnemyParameter.h"

AllyParameter::AllyParameter()
    : name(""),
    hp(0),
    mp(0),
    maxHp(0),
    maxMp(0),
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

int AllyParameter::healHp(int amount)
{   
    int before = hp;
    hp += amount;
    if (hp > maxHp)
    {
        hp = maxHp;
    }
    return hp - before;
}

int AllyParameter::consumeMp(int amount)
{
    int before = mp;
    mp -= amount;
    if (mp < 0)
    {
        mp = 0;
    }
    return mp - before;
}

int AllyParameter::healMp(int amount)
{
    int before = mp;
    mp += amount;
    if (mp > maxMp)
    {
        mp = maxMp;
    }
    return mp - before;
}


int AllyParameter::getHp()
{
    return hp;
}

int AllyParameter::getMp()
{
    return mp;
}
const int AllyParameter::getAttack() const
{
    return attackPower;
}
const int AllyParameter::getDefense() const
{
    return defensePower;
}
void AllyParameter::addExp(int exp)
{
    gainedExp += gainedExp;
}