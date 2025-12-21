#include"FieldEnemy.h"
#include"DxLib.h"
#include"EnemyParameter.h"

FieldEnemy::FieldEnemy() {}

FieldEnemy::FieldEnemy(const Position pos, EnemyParameter parameter)
    : pos(pos),
    parameter(std::move(parameter))
{
}

void FieldEnemy::spawn(int maxX, int maxY, RandomGenerator& rng)
{
    auto [randX, randY] = pos.getRandomPosition(maxX, maxY, rng);

    pos.x = randX;
    pos.y = randY;
    isActive = true;
}

void FieldEnemy::draw() const
{
    if (!isActive)
    {
        return;
    }

    int color = GetColor(255, 0, 0);
    DrawString(pos.x, pos.y, parameter.getName().c_str(), color);
}
void FieldEnemy::setEncountered()
{
    isActive = false;
}
bool FieldEnemy::getIsActive() const
{
    return isActive;
}
void FieldEnemy::setIsActive(bool state)
{
    isActive = state;
}
int FieldEnemy::getX() {
    return pos.getX();
}

int FieldEnemy::getY() {
    return pos.getY();
}
const Position& FieldEnemy::getPosition() const {
    return pos;
}
const EnemyParameter& FieldEnemy::getParameter() const{
    return parameter;
}