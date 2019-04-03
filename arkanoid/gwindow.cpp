#include "gwindow.h"

gWindow::gWindow(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    group_blocks = new QGraphicsItemGroup();
    group_plate = new QGraphicsItemGroup();
    group_balls = new QGraphicsItemGroup();
    scene->addItem(group_blocks);
    scene->addItem(group_plate);
    scene->addItem(group_balls);
    this->setScene(scene);
    brickPen.setColor(Qt::red);
}

void gWindow::addBrick(point pos, point sz)
{
    bricks.push_back(new brick(pos, sz));
}

void gWindow::addPlatform()
{
    platf = new platform();
}

void gWindow::redrawBricks()
{
    for(auto i: group_blocks->childItems())
    {
        scene->removeItem(i);
    }

    for(auto i : bricks)
    {
        group_blocks->addToGroup(scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, brickPen));
    }
}

void gWindow::redrawPlate()
{

}

void gWindow::totalRedraw()
{
    redrawPlate();
    redrawBricks();
}

int gWindow::bricksCount()
{
    return bricks.size();
}

brick* gWindow::getBrick(int i)
{
    return this->bricks[i];
}
