#include "ball.h"

QRectF ball::boundingRect() const
{

}

void ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

ball::ball(point pos, point size, point init_vel)
{
    this->pos = pos;
    this->size = size;
    this->velocity = init_vel;
}

point ball::getPos()
{
    return this->pos;
}

point ball::getSize()
{
    return this->size;
}

point ball::getVelocity()
{
    return this->velocity;
}

ball::ball(point pos, point velocity, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->pos = pos;
    this->velocity = velocity;
}

void ball::move()
{
    this->pos.x += this->velocity.x;
    this->pos.y += this->velocity.y;
}

void ball::teleport(point newPos)
{
    this->pos = newPos;
}

void ball::changeDir(point newVelocity)
{
    this->velocity.x = newVelocity.x;
    this->velocity.y = newVelocity.y;
}

