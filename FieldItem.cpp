#include"FieldItem.h"
#include"DxLib.h"
#include <time.h>

FieldItem::FieldItem()
    : item(), pos({ 0, 0 }), isActive(false)
{
    srand(static_cast<unsigned>(time(nullptr))); // ‰‰ñ‚Ì‚İ—”‰Šú‰»
}
void FieldItem::spawn(const Item& newItem, int maxX, int maxY)
{
    item = newItem;
    pos.x = rand() % maxX;
    pos.y = rand() % maxY;
    isActive = true;
}
void FieldItem::draw() const
{
    if (!isActive) return;

    int color = GetColor(255, 255, 0);
    DrawString(pos.x, pos.y, item.getName().c_str(), color);
}
void FieldItem::isGotten()
{
    isActive = false;
}
bool FieldItem::getIsActive() const
{
    return isActive;
}
int FieldItem::getX() {
    return pos.getX();
}

int FieldItem::getY() {
    return pos.getY();
}