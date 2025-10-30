#pragma once
#include"Name.h"
#include"Position.h"


class FieldItem {
private:
	Item item;
	Position pos;
	bool isActive;
public:
	void spawn();
	void disappear();

};