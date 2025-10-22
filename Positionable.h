#pragma once
#include"Position.h"

class Positionable {
protected:
	Position pos;
public:
	std::pair<int, int> getPosition() const;

	void setPosition(int x, int y);
};