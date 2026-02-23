#pragma once
#include<string>
#include<vector>

class Display;

class FieldMenuDrawer {
public:
	void draw(
		Display& display,
		const std::vector<std::string>& items,
		int selectedIndex,
		int x,
		int y
	) const;
};