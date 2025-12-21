#include"HitCheck.h"

bool HitCheck::check(const Position& allyPosition, const Position& object)
{
    int dx = allyPosition.getX() - object.getX();
    int dy = allyPosition.getY() - object.getY();

    float distance = (dx * dx + dy * dy);

    return (distance < 30.0f * 30.0f);
}