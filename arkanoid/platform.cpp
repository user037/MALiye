#include "platform.h"
QRectF platform::boundingRect() const
{

}

void platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

platform::platform(point pos, point maxPos, point minPos, int velocity, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->pos = pos;
    this->maxPos = maxPos;
    this->minPos = minPos;
    this->velocity = velocity;
}

point platform::getPos()
{
    return this->pos;
}

point platform::getSize()
{
    return this->size;
}

int platform::getVelocity()
{
    return this->velocity;
}

void platform::move(bool dir)
{
    if(dir) //move to the right
    {
        this->pos.x += this->velocity;
    }
    else //move to the left
    {
        this->pos.x -= this->velocity;
    }
    if(this->pos.x > this->maxPos.x) //outside the screen
    {
        this->pos.x = this->maxPos.x;
    }
    if(this->pos.x < this->minPos.x)
    {
        this->pos.x = this->minPos.x;
    }
}




