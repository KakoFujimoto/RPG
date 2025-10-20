#include "Neko.h"

Neko::Neko()
	: parameter("‚Ë‚±", 20, 0, 13, 7, 8, 1, 0){};

AllyParameter& Neko::getParameter()
{
	return parameter;
}

std::string Neko::getName()
{
	return parameter.name;
}