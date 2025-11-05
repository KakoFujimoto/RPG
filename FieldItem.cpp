#include"FieldItem.h"
#include"DxLib.h"
#include <time.h>

FieldItem::FieldItem()
    : item(), pos({ 0, 0 }), isActive(false){}

void FieldItem::spawn(const Item& newItem, int maxX, int maxY, RandomGenerator& rng)
{
    item = newItem;
    auto [randX, randY] = rng.getRandomPosition(maxX, maxY);

    pos.x = randX;
    pos.y = randY;
    isActive = true;
}

void FieldItem::draw() const
{
    if (!isActive) return;

    int color = GetColor(255, 255, 0);
    DrawString(pos.x, pos.y, item.getName().c_str(), color);
}
void FieldItem::setGotten()
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
const Position& FieldItem::getPosition() const { 
    return pos;
}

 const Item& FieldItem::getItemData() const{
     return item;
}