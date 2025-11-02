#include"GameManager.h"

bool GameManager::HitCheck(const Position& allyPosition, const Position& object)
{
    int dx = allyPosition.getX() - object.getX();
    int dy = allyPosition.getY() - object.getY();
    float distance = std::sqrt(dx * dx + dy * dy);

    return (distance < 10.0f);
}