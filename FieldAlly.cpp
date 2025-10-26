#include "FieldAlly.h"
#include "DxLib.h"

FieldAlly::FieldAlly(std::string name, int x, int y)
    : pos(x, y)
{
    this->parameter.name = std::move(name);
}

void FieldAlly::move() {
    auto [x, y] = getPosition();

    if (CheckHitKey(KEY_INPUT_UP))
    {
        y -= 5;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        y += 5;
    }
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        x -= 5;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        x += 5;
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
