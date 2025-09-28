#pragma once
#include <utility>

class Position {
private:
	std::pair<int, int> _pos{ 0,0 };

public:
	void setPosition(int x, int y);
	std::pair<int, int> getPosition() const;
};