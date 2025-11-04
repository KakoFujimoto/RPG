#pragma once
#include"RandomGenerator.h"
#include"Position.h"
#include"FieldItem.h"
#include"FieldAlly.h"
#include"ItemBag.h"

class GameManager {
private:
	//RandomGenerator rng;
	FieldItem fieldItem;
	FieldAlly ally;
	ItemBag itemBag;
public:
	GameManager();
	//RandomGenerator getRng() { return rng; }
	bool HitCheck(const Position& allyPosition, const Position& object);
	void updateItemBag();
	ItemBag& getItemBag();
	FieldItem& getFieldItem() { return fieldItem; }
	FieldAlly& getAlly() { return ally; }
	//ItemBag& getItemBag() { return itemBag; }
};