#include "gwindow.h"

gWindow::gWindow(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    group_bg = new QGraphicsItemGroup();
    group_blocks = new QGraphicsItemGroup();
    group_plate = new QGraphicsItemGroup();
    group_balls = new QGraphicsItemGroup();
    scene->addItem(group_blocks);
    scene->addItem(group_plate);
    scene->addItem(group_balls);
    scene->addItem(group_bg);
    group_bg->setZValue(-10);
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    group_bg->addToGroup(scene->addRect(0,0,1000,1000,blackPen,blackBrush));
    group_balls->setZValue(10);
    this->setScene(scene);
    QImage plateTexture("/home/user/git/maliye/arkanoid/img/panel.bmp");
    QImage ballTexture("/home/user/git/maliye/arkanoid/img/ball.bmp");
    QImage brickTexture("/home/user/git/maliye/arkanoid/img/brick-base.bmp");
    plateBrush = new QBrush(plateTexture);
    ballBrush = new QBrush(ballTexture);
    brickBrush = new QBrush(brickTexture);
    nonePen.setColor(Qt::black);
    nonePen.setWidth(-1);
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
        if(i->getId() != 0)
        {
            QTransform btransf = i->transform();
            brickBrush->setTransform(btransf);
            group_blocks->addToGroup(scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, nonePen,*brickBrush));
        }
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
        group_blocks->addToGroup(scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, nonePen, *ballBrush));
        group_blocks->childItems()[group_blocks->childItems().size()-1]->setZValue(10);
    }
    group_balls->setZValue(10);
}

void gWindow::redrawPlatform()
{
    for(auto i : group_plate->childItems())
    {
        scene->removeItem(i);
    }
    group_plate->addToGroup(scene->addRect(0, 0, this->platf->getSize().x, this->platf->getSize().y, nonePen));
    group_plate->addToGroup(scene->addRect(0, 0, this->platf->getSize().x + 40, this->platf->getSize().y + 40, nonePen,*plateBrush));
        this->plateBrush->setTransform(group_plate->childItems()[0]->transform());
    group_plate->childItems()[0]->setPos(this->platf->getPos().x, this->platf->getPos().y);
    group_plate->childItems()[1]->setPos(this->platf->getPos().x - 20, this->platf->getPos().y - 20);
    group_blocks->childItems()[0]->setZValue(0);
    group_blocks->childItems()[1]->setZValue(5);
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
        return 1;
    }
    if(item->getPos().y < 0)
    {
        return 2;
    }
    if(item->getPos().x > 750)
    {
        return 3;
    }
    if(item->getPos().y > 550)
    {
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
