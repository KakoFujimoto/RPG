#pragma once
#include <utility>

class Position {
public:
	int x;
	int y;

	Position(int x, int y);

	int getX() const;
	int getY() const;
};