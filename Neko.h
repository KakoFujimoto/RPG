#pragma once
#include "AllyParameter.h"
#include"ICharacter.h"

class Neko : public ICharacter{
private:
	AllyParameter parameter;
public:
	Neko();
	AllyParameter& getParameter();
	std::string getName();
};


class Inu : public ICharacter {
private:
	AllyParameter parameter;
public:
	Neko();
	AllyParameter& getParameter();
	std::string getName();
};


//--------------------------------------------------------

class FieldAlly : public ICharacter {
private:
	AllyParameter parameter;
public:
	FieldAlly(std::string name)
	{
		this->parameter.name = name;
	}

	AllyParameter& getParameter();
	std::string getName() { return parameter.name; }

	std::pair<int, int> getPosition() const;
	void setPosition(int x, int y);
	void move();
};


class Neko : public FieldAlly {
private:
public:
	Neko() : FieldAlly("ネコ")
	{ }

	void move()
	{
		if (CheckHitKey(KEY_INPUT_UP))
		{
			y += 5;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y -= 5;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x += 5;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x -= 5;
		}
	}

};


class Inu : public FieldAlly {
private:
	AllyParameter parameter;
public:
	Inu() : FieldAlly("イヌ")
	{}

	void move()
	{
		if (CheckHitKey(KEY_INPUT_UP))
		{
			y -= 5;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y += 5;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x -= 5;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x += 5;
		}

	}
};

void f()
{
	FieldAlly* neko = new FieldAlly("ネコ");

	//FieldAlly* neko = new Neko();
	//neko->getName();	// "ネコ"


	//FieldAlly* inu = new Inu();
	//inu->getName();	// "イヌ"
}