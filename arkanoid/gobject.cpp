#include "gobject.h"

gObject::gObject() : QGraphicsItem()
{

}

void gObject::setPos(point newPos)
{
    this->pos = newPos;
}

void gObject::setSpeed(point newSpeed)
{
    this->speed = newSpeed;
}

void gObject::xBounce()
{
    this->speed.x = this->speed.x * -1;
}

void gObject::yBoubce()
{
    this->speed.y = this->speed.y * -1;
}
