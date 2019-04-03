#ifndef GOBJECT_H
#define GOBJECT_H
#include <QGraphicsItem>
#include <tools.h>

class gObject : QGraphicsItem
{
public:
    gObject();
    point pos; //from top-left corner
    point size; //px from top-left corner
    point speed; // px/frame
    void setPos(point newPos);
    void setSpeed(point newSpeed);
    void xBounce();
    void yBoubce();
};

#endif // GOBJECT_H
