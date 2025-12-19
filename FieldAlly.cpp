#include "FieldAlly.h"
#include "DxLib.h"
#include "EffectResult.h"

FieldAlly::FieldAlly() {}

FieldAlly::FieldAlly(const Position pos, AllyParameter parameter)
    : pos(pos),
    parameter(std::move(parameter))
{
}

void FieldAlly::addPositionX(int x) {
    pos.x += x;
}


void FieldAlly::addPositionY(int y) {
    pos.y += y;
}

void FieldAlly::move() {

    if (CheckHitKey(KEY_INPUT_UP))
    {
        addPositionY(-5);
    }
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        addPositionY(5);
    }
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        addPositionX(-5);
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        addPositionX(5);
    }
}

AllyParameter& FieldAlly::getParameter() {
    return parameter;
}

std::string FieldAlly::getName() {
    return parameter.name;
}

int FieldAlly::getX() {
    return pos.getX();
}

int FieldAlly::getY() {
    return pos.getY();
}

EffectResult FieldAlly::useItem(const Item& item)
{
    if (item.getAmount() <= 0)
    {
        EffectResult result;
        result.success = false;
        return result;
    }
    return item.getEffect().apply(parameter);
}


EffectResult FieldAlly::castSpell(const Spell& spell)
{
    EffectResult result;
    result.success = false;

    // MP•s‘«
    if (parameter.getMp() < spell.getMpCost()) {
        return result;
    }

    int beforeHp = parameter.getHp();
    int beforeMp = parameter.getMp();

    parameter.consumeMp(spell.getMpCost());
    spell.getEffect().apply(parameter);

    result.success = true;
    result.userName = parameter.name;
    result.itemName = spell.getName();

    result.hpDelta = parameter.getHp() - beforeHp;
    result.mpDelta = parameter.getMp() - beforeMp;

    return result;
}