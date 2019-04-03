#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>
#include <tools.h>

class brick : public QGraphicsItem
{
private:
    point pos;
    point size;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
public:
    point getPos();
    point getSize();
    brick(point pos, point sz, QGraphicsItem *parent = nullptr);
    void setPos(point newPos);
};

#endif // BRICK_H
