#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>
#include <tools.h>

class platform : public QGraphicsItem
{
public:
    platform();
    point getPos();
    point getMaxPos();
    point getMinPos();
    int getVelocity();
    platform(point pos, point maxPos, point minPos, int velocity, QGraphicsItem *parent = nullptr);
    void move(bool dir);

private:
    point pos;
    point maxPos;
    point minPos;
    int velocity;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // PLATFORM_H
