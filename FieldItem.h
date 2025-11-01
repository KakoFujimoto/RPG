#pragma once
#include"Position.h"
#include"Item.h"
#include"Display.h"


class FieldItem {
private:
	Item item;
	Position pos;
	bool isActive;
public:
	//void spawn();
	//void isGotten();
	FieldItem();
	void spawn(const Item& newItem, int maxX, int maxY);
	void draw() const;
};