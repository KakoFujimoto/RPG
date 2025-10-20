#include "FieldAlly.h"
#include "DxLib.h"

FieldAlly::FieldAlly(ICharacter* c)
    : character(c){ }

void FieldAlly::move() {
    auto [x, y] = pos.getPosition();

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

    pos.setPosition(x, y);
}

std::pair<int, int> FieldAlly::getPosition() const
{
    return pos.getPosition();
}

void FieldAlly::setPosition(int x, int y) {
    pos.setPosition(x, y);
}