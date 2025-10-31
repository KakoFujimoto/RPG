#pragma once
#include"Position.h"
#include"Item.h"


class FieldItem {
private:
	Item item;
	Position pos;
	bool isActive;
public:
	void spawn();
	void disappear();

};