#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <tools.h>

class ball : public QGraphicsItem
{
public:
    QString getClass() {return "ball";}
    ball(point pos, point size, point init_vel);
    point getPos();
    point getSize();
    point getVelocity();
    ball(point pos, point velocity, QGraphicsItem *parent = nullptr);
    void move();
    void teleport(point newPos);
    void changeDir(point newVelocity);
private:
    point pos;
    point size;
    point velocity;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // BALL_H
