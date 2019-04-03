#ifndef GWINDOW_H
#define GWINDOW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <tools.h>
#include <brick.h>
#include <QDebug>

class gWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit gWindow(QWidget *parent = nullptr);

    void addBrick(point pos, point sz);
    void redrawBricks();
private:
    QGraphicsScene *scene;
    QVector<brick*> bricks;
    QPen brickPen;
signals:

public slots:
};

#endif // GWINDOW_H
