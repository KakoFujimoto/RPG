#pragma once
#include"Position.h"
#include"Item.h"
#include"Display.h"
#include"RandomGenerator.h"


class FieldItem {
private:
	Item item;
	Position pos;
	bool isActive;
public:
	FieldItem();
	void spawn(const Item& newItem, int maxX, int maxY, RandomGenerator& rng);
	void draw() const;
	void setGotten();
	bool getIsActive() const;
	int getX();
	int getY();
	const Position& getPosition() const;
	const Item& getItemData() const;
};