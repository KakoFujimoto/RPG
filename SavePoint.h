#pragma once
#include"Name.h"
#include"Position.h"


class SavePoint {
private:
	Name name;
	Position _pos;
public:
	void saveGame();
};