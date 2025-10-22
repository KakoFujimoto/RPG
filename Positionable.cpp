#include"Positionable.h"

std::pair<int, int> Positionable::getPosition() const {
	return pos.getPosition();
}

void Positionable::setPosition(int x, int y) {
	pos.setPosition(x, y);
}