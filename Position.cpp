#include "Position.h"

Position::Position() {}

Position::Position(int x, int y)
	: x(x),y(y)
{
}
int Position::getX() const {
	return x;
}
int Position::getY() const {
	return y;
}
Position Position::getRandomPosition(int maxX, int maxY, RandomGenerator& rng)
{
	int randX = rng.getRandomValue(0, maxX - 1);
	int randY = rng.getRandomValue(0, maxY - 1);
	return Position(randX, randY);
}
