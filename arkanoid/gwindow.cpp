#include "gwindow.h"

gWindow::gWindow(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setScene(scene);
    brickPen.setColor(Qt::red);
}

void gWindow::addBrick(point pos, point sz)
{
    bricks.push_back(new brick(pos, sz));
}

void gWindow::redrawBricks()
{
    scene->clear();
    for(auto i : bricks)
    {
        scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, brickPen);
        qDebug() << i->getPos().x << " " << i->getPos().y;
        qDebug() << i->getSize().x << " " << i->getSize().y;
    }
}

int gWindow::bricksCount()
{
    return bricks.size();
}

brick* gWindow::getBrick(int i)
{
    return this->bricks[i];
}
