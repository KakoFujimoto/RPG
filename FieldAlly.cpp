#include "FieldAlly.h"
#include "DxLib.h"

FieldAlly::FieldAlly(std::string name)
{
    this->parameter.name = name;
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

    setPosition(x, y);
}

AllyParameter& FieldAlly::getParameter() {
    return parameter;
}

std::string FieldAlly::getName() {
    return parameter.name;
}
