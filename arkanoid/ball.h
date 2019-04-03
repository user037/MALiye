#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <tools.h>

class ball : public QGraphicsItem
{
public:
    point getPos();
    point getVelocity();
    ball(point pos, point velocity, QGraphicsItem *parent = nullptr);
    void move();
    void changeDir(point newVelocity);
private:
    point pos;
    point velocity;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // BALL_H
