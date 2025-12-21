#pragma once
#include"Position.h"
#include"FieldItem.h"
#include"FieldItemManager.h"
#include"FieldAlly.h"
#include"ItemBag.h"
#include"HitCheck.h"
#include"FieldEnemyManager.h"

class GameManager {
private:
	FieldAlly ally;
	ItemBag itemBag;
	FieldItemManager fieldItemManager;
	FieldEnemyManager fieldEnemyMamager;
	HitCheck hitCheck;
public:
	GameManager();
	void updateItemBag();
	ItemBag& getItemBag();
	FieldItemManager& getFieldItemManager();
	FieldEnemyManager& getFieldEnemyManager();
	FieldAlly& getAlly();
	void checkEncount();
};