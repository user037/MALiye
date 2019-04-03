#include "brick.h"

QRectF brick::boundingRect() const
{

}

void brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
}

void brick::setPos(point newPos)
{
    this->pos = newPos;
}

void brick::hit()
{
    if(this->id > 0)
    {
        --this->id;
    }
}
