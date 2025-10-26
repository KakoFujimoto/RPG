#include "FieldAlly.h"
#include "DxLib.h"

FieldAlly::FieldAlly(std::string name, int x, int y)
    : pos(x,y)
{
    this->parameter.name = std::move(name);
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