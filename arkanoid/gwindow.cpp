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
    QPixmap plateTexture("C:/MALiye/arkanoid/img/panel.bmp");
    plateBrush.setTexture(plateTexture);
    brickPen.setColor(Qt::red);
    platePen.setWidth(1);
}

void gWindow::addBrick(point pos, point sz, int id)
{
    bricks.push_back(new brick(pos, sz, id));
}

void gWindow::addPlatform()
{
    platf = new platform({325,500},{800-160,600-25},{0,0}, 15);
}

void gWindow::addBall(point pos, point size, point init_vel)
{
    balls.push_back(new ball(pos,size,init_vel));
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

void gWindow::redrawBalls()
{
    for(auto i: group_balls->childItems())
    {
        scene->removeItem(i);
    }

    for(auto i : balls)
    {
        group_blocks->addToGroup(scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, brickPen));
    }
}

void gWindow::redrawPlatform()
{
    for(auto i : group_plate->childItems())
    {
        scene->removeItem(i);
    }
    group_plate->addToGroup(scene->addRect(0, 0, this->platf->getSize().x, this->platf->getSize().y, brickPen));
    group_plate->addToGroup(scene->addRect(0, 0, this->platf->getSize().x + 40, this->platf->getSize().y + 40, platePen,plateBrush));
        plateBrush.setTransform(group_plate->childItems()[0]->transform());
    group_plate->childItems()[0]->setPos(this->platf->getPos().x, this->platf->getPos().y);
    group_plate->childItems()[1]->setPos(this->platf->getPos().x - 20, this->platf->getPos().y - 20);
}

void gWindow::totalRedraw()
{
    redrawPlatform();
    redrawBricks();
    redrawBalls();
}

int gWindow::bricksCount()
{
    return bricks.size();
}

int gWindow::ballsCount()
{
    return balls.size();
}

int gWindow::isBallInBound(ball *item) //0 - in bound, 1 - left wall, ..., 4 - bottom wall
{
    if(item->getPos().x < 0)
    {
        item->changeDir({-item->getVelocity().x, item->getVelocity().y});
        return 1;
    }
    if(item->getPos().y < 0)
    {
        item->changeDir({item->getVelocity().x, -item->getVelocity().y});
        return 2;
    }
    if(item->getPos().x > 750)
    {
        item->changeDir({-item->getVelocity().x, item->getVelocity().y});
        return 3;
    }
    if(item->getPos().y > 550)
    {
        item->changeDir({item->getVelocity().x, -item->getVelocity().y});
        return 4;
    }
    return 0;
}

bool gWindow::hasInBricks(QGraphicsItem &it)
{
    bool has = 0;
    for(auto i : bricks)
    {
        if(i == &it) has = 1;
    }
    return has;
}

brick* gWindow::getBrick(int i)
{
    return this->bricks[i];
}

ball* gWindow::getBall(int i)
{
    return this->balls[i];
}
