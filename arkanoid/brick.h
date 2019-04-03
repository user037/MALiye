#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>
#include <tools.h>

class brick : public QGraphicsItem
{
public:
    point getPos();
    point getSize();
    int getId();
    brick(point pos, point sz, int id, QGraphicsItem *parent = nullptr);
    void setPos(point newPos);
    void hit();
private:
    point pos;
    point size;
    int id;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // BRICK_H
