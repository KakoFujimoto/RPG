#pragma once
#include <utility>

class Position {
public:
	Position(int x, int y) : _pos(x, y) {}
	std::pair<int, int> getPosition() const;
	std::pair<int, int> _pos{ 0,0 };
};