#pragma once
#include <utility>

class Position {
public:
	int x;
	int y;

	std::pair<int, int> _pos{ 0,0 };
	Position(int x, int y) : _pos(x, y) {}
	std::pair<int, int> getPosition() const;
};