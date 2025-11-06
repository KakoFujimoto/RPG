#pragma once
#include <utility>
#include"RandomGenerator.h"

class Position {
public:
	int x;
	int y;

	Position();
	Position(int x, int y);

	int getX() const;
	int getY() const;

	Position getRandomPosition(int maxX, int maxY, RandomGenerator& rng);

};