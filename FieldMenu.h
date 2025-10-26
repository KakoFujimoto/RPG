#pragma once
#include<string>

class FieldMenu {
private:
	std::string menuItems[4] =
	{ "‚Ç‚¤‚®",
	"‚Â‚æ‚³",
	"‚¶‚ã‚à‚ñ",
	"‚à‚Ç‚é" };
public:
	void open();
	void choose();
	void select();
	void close();
};