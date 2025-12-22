#pragma once
#include"Position.h"
#include"FieldItem.h"
#include"FieldItemManager.h"
#include"FieldAlly.h"
#include"ItemBag.h"
#include"HitCheck.h"
#include"FieldEnemyManager.h"
#include"BattleStartInfo.h"
#include"BattleWindowRenderer.h"


class Display;
class GameManager {
private:
	FieldAlly ally;
	ItemBag itemBag;
	FieldItemManager fieldItemManager;
	FieldEnemyManager fieldEnemyManager;
	HitCheck hitCheck;
	bool isInBattle = false;
	BattleStartInfo currentBattleInfo;
	BattleWindowRenderer battleWindowRenderer;
public:
	GameManager(Display& display);
	void updateItemBag();
	ItemBag& getItemBag();
	FieldItemManager& getFieldItemManager();
	FieldEnemyManager& getFieldEnemyManager();
	FieldAlly& getAlly();
	bool checkEncount();
	bool isBattle() const;
	void setBattle(bool v);
	void update();
	const BattleStartInfo& getBattleInfo() const;
	void endBattle();
	int getBattleMenuCount() const;
	BattleWindowRenderer& getBattleWindowRenderer();
};