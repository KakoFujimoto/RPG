#pragma once
#include"Position.h"
#include"FieldItem.h"
#include"FieldItemManager.h"
#include"FieldAlly.h"
#include"ItemBag.h"
#include"HitCheck.h"

class GameManager {
private:
	FieldAlly ally;
	ItemBag itemBag;
	FieldItemManager fieldItemManager;
	HitCheck hitCheck;
public:
	GameManager();
	void updateItemBag();
	ItemBag& getItemBag();
	FieldItemManager& getFieldItemManager();
	FieldAlly& getAlly();
};