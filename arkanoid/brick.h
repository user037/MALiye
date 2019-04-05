#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>
#include <tools.h>

class brick : public QGraphicsItem
{
public:
    QString getClass() {return "brick";}
    point getPos();
    point getSize();
    int getId();
    brick(point pos, point sz, int id, QGraphicsItem *parent = nullptr);
    void setPos(point newPos);
    void hit();
    void setPrice(int price);
    int getPrice();
private:
    point pos;
    int price;
    point size;
    int id;
    QRectF boundingRect() const; //for compatibility
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr); //for compatibility

};

#endif // BRICK_H
