#pragma once
#include<string>
#include<vector>
#include"Display.h"
#include"GameManager.h"
#include"Item.h"


class FieldMenu {
private:
	std::vector<std::string> menuItems{
	"どうぐ",
	"つよさ",
	"じゅもん",
	"もどる"
	};

	bool isOpen = false;
	bool isItemListOpen = false;
	bool isParameterOpen = false;
	bool isSpellListOpen = false;
	int selectedIndex = 0;
	GameManager* gm;

	IMenu* submenu;

public:
	FieldMenu(GameManager* gm);
	void choose();
	void select();
	void open();
	void close();
	void update();
	void draw(Display& display);
	bool getIsOpen () const;
	void drawItemList();
	void drawParameter();
	void drawSpellList();
	

};




/** 新しく追加したインターフェース -> 各メニューの抽象化(ルート、どうぐ、呪文など) */
class IMenu {
public:
	virtual void update() = 0;
	virtual void draw(Display& display) = 0;
};


/** FieldMenu */
class FieldMenu2 {
public:
	void open();

	void draw()
	{
		std::for_each(menus.begin(), menus.end(), [](auto& item) {
			item.draw();
		});
	}

	void update()
	{
		if (menus.size() > 0) {
			auto& lastMenu = menus[menus.size() - 1];
			lastMenu.update();
		}
	}

	void addMenu(IMenu* menu) { menus.push_back(menu); }

private:
	std::vector<std::shared_ptr<IMenu>> menus;
};