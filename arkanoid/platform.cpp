#include "platform.h"
QRectF platform::boundingRect() const
{

}

void platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

platform::platform()
{

}

point platform::getPos()
{
    return this->pos;
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




