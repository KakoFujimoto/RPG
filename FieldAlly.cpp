#include "FieldAlly.h"
#include "DxLib.h"

FieldAlly::FieldAlly(std::string name, int x, int y)
    : pos(x, y)
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
    //auto [x, y] = getPosition();

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
    pos._pos = { x,y };
}

AllyParameter& FieldAlly::getParameter() {
    return parameter;
}

std::string FieldAlly::getName() {
    return parameter.name;
}

std::pair<int, int> FieldAlly::getPosition(){
    return pos.getPosition();
}
