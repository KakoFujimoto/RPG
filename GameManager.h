#pragma once
//#include"RandomGenerator.h"
#include"Position.h"
#include"FieldItem.h"
#include"FieldAlly.h"
#include"ItemBag.h"
#include"HitCheck.h"

class GameManager {
private:
	FieldItem fieldItem;
	FieldAlly ally;
	ItemBag itemBag;
	HitCheck hitCheck;
public:
	GameManager();
	void updateItemBag();
	ItemBag& getItemBag();
	FieldItem& getFieldItem() { return fieldItem; }
	FieldAlly& getAlly() { return ally; }
	//ItemBag& getItemBag() { return itemBag; }
};