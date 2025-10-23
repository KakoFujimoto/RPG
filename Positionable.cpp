#include"Positionable.h"

std::pair<int, int> Positionable::getPosition() const {
	return pos._pos;
}

void Positionable::setPosition(int x, int y) {
	pos._pos = { x,y };
}