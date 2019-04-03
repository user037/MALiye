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

brick::brick(point pos, point sz, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->pos = pos;
    this->size = sz;
}

void brick::setPos(point newPos)
{
    this->pos = newPos;
}
