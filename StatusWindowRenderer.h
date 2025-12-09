#pragma once
#include<DxLib.h>
#include "Display.h"
#include"AllyParameter.h"

class AllyParameter;
class Display;
class StatusWindowRenderer {
private:
    Display& display;

public:
    StatusWindowRenderer(Display& d);
    void show(const AllyParameter& p, int x, int y);
  
};
