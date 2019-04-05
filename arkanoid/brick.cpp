#include "brick.h"

QRectF brick::boundingRect() const //for compatibility
{

}

void brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //for compatibility
{

}

point brick::getPos()
{
    return this->pos;
}

point brick::getSize()
{
    return this->size;
}

int brick::getId()
{
    return this->id;
}

brick::brick(point pos, point sz, int id, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->pos = pos;
    this->size = sz;
    this->id = id;
}

void brick::setPos(point newPos)
{
    this->pos = newPos;
}

void brick::hit()
{
    if(this->id > 0)
    {
        this->id = this->id - 1;
    }
}

void brick::setPrice(int price)
{
    this->price = price;
}

int brick::getPrice()
{
    return this->price;
}
