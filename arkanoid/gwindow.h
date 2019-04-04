#ifndef GWINDOW_H
#define GWINDOW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <tools.h>
#include <brick.h>
#include <ball.h>
#include <platform.h>
#include <QDebug>

class gWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit gWindow(QWidget *parent = nullptr);

    void addBrick(point pos, point sz, int id);
    void addPlatform();
    void addBall(point pos, point size, point init_vel);
    void redrawBricks();
    void redrawBalls();
    void redrawPlatform(); //plate = platform
    void totalRedraw();
    int bricksCount();
    int ballsCount();
    int isBallInBound(ball *item);
    bool hasInBricks(QGraphicsItem &it);
    QGraphicsScene *scene;
    QGraphicsItemGroup *group_blocks;
    QGraphicsItemGroup *group_plate;
    QGraphicsItemGroup *group_balls;
    brick* getBrick(int i);
    ball* getBall(int i);
    platform *platf;
private:
    QVector < brick* > bricks;
    QVector < ball* > balls;
    QPen brickPen;
    QPen platePen;
    QBrush plateBrush;
signals:

public slots:
};

#endif // GWINDOW_H
