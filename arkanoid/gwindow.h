#ifndef GWINDOW_H
#define GWINDOW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <tools.h>
#include <brick.h>
#include <platform.h>
#include <QDebug>

class gWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit gWindow(QWidget *parent = nullptr);

    void addBrick(point pos, point sz, int id);
    void addPlatform();
    void redrawBricks();
    void redrawPlatform(); //plate = platform
    void totalRedraw();
    int bricksCount();
    brick* getBrick(int i);
    platform *platf;
private:
    QGraphicsScene *scene;
    QGraphicsItemGroup *group_blocks;
    QGraphicsItemGroup *group_plate;
    QGraphicsItemGroup *group_balls;
    QVector < brick* > bricks;
    QPen brickPen;
signals:

public slots:
};

#endif // GWINDOW_H
