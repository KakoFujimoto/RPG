#include "Position.h"

void Position::setPosition(int x, int y)
{
	_pos = { x,y };
}

std::pair<int, int> Position::getPosition() const {
	return _pos;
}