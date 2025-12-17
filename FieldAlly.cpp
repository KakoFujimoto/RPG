#include "FieldAlly.h"
#include "DxLib.h"

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

void FieldAlly::useItem(const Item& item)
{   
    if (item.getAmount() <= 0)
    {
        return;
    }
    item.getEffect().apply(parameter);
}

void FieldAlly::castSpell(const Spell& spell)
{
    if (parameter.getMp() >= spell.getMpCost()) {
        parameter.consumeMp(spell.getMpCost());
        spell.getEffect().apply(parameter);
    }
}