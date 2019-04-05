#include "gwindow.h"

    QColor midColor(QColor a, QColor b)
    {
        QColor out((a.red()*b.red())/256,(a.green()*b.green())/256,(a.blue()*b.blue())/256);
        return out;
    }

    QColor mixColor(QColor a, QColor b)
    {
        QColor out((a.red()+b.red())/2,(a.green()+b.green())/2,(a.blue()+b.blue())/2);
        return out;
    }

    QImage colorImage(QImage *src, QColor col)
{
    QImage img = *src;
    for(int y = 0; y < src->height(); y++)
    {
        for(int x = 0; x < src->width(); x++)
        {
            img.setPixelColor(x,y,midColor(img.pixel(x,y),col.rgb()));
        }
    }
    return img;
}

gWindow::gWindow(QWidget *parent) : QGraphicsView(parent)
{
    score = new QGraphicsSimpleTextItem("SCORE: 0");
    score->setPos(25,25);
    score->setBrush(QBrush(Qt::white));
    QFontDatabase::addApplicationFont(QDir::currentPath() + "/../arkanoid/res/PressStart2P.ttf");
    QFont font("PressStart2P");
    font.setWeight(16);
    score->setFont(font);
    score->setZValue(1000);

    brickColor.resize(6); //Initializing color list
    brickColor[0] = Qt::white; //not rendering [0]
    brickColor[1] = mixColor(Qt::blue,mixColor(Qt::blue,Qt::white));
    brickColor[2] = Qt::red;
    brickColor[3] = Qt::yellow;
    brickColor[4] = mixColor(Qt::red,Qt::yellow); //orange
    brickColor[5] = Qt::green;

    scene = new QGraphicsScene();
    group_bg = new QGraphicsItemGroup();
    group_blocks = new QGraphicsItemGroup();
    group_plate = new QGraphicsItemGroup();
    group_balls = new QGraphicsItemGroup();
    scene->addItem(group_blocks);
    scene->addItem(group_plate);
    scene->addItem(group_balls);
    scene->addItem(group_bg);
    scene->addItem(score);
    group_plate->setFlag(QGraphicsItem::ItemNegativeZStacksBehindParent);
    group_bg->setFlag(QGraphicsItem::ItemNegativeZStacksBehindParent);
    group_bg->setZValue(-10);
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    group_bg->addToGroup(scene->addRect(0,0,1000,1000,blackPen,blackBrush));
    this->setScene(scene);

    plateTexture = new QImage(QDir::currentPath() + "/../arkanoid/img/panel.bmp");
    ballTexture = new QImage(QDir::currentPath() + "/../arkanoid/img/ball.bmp");
    brickTexture = new QImage(QDir::currentPath() + "/../arkanoid/img/brick-base.bmp");
    qDebug() << QDir::currentPath();

    plateBrush = new QBrush(*plateTexture);
    ballBrush = new QBrush(*ballTexture);
    brickBrush = new QBrush(*brickTexture);
    nonePen.setColor(Qt::black);
    nonePen.setWidth(-1);
}

void gWindow::addBrick(point pos, point sz, int id)
{
    bricks.push_back(new brick(pos, sz, id));
}

void gWindow::addPlayer()
{
    pl = new player(0, 0, 2, 2, 0);
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
            QTransform btransf;
            btransf.translate(i->getPos().x, i->getPos().y);
            brickBrush->setTransform(btransf);
            QBrush tmpBrush = *brickBrush;
            brickBrush->setTextureImage(colorImage(brickTexture ,brickColor[i->getId()]));
            group_blocks->addToGroup(scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, nonePen,*brickBrush));
            group_blocks->childItems()[group_blocks->childItems().size()-1]->setZValue(3);
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
        QTransform btransf;
        btransf.translate(i->getPos().x, i->getPos().y);
        ballBrush->setTransform(btransf);
        group_blocks->addToGroup(scene->addRect(i->getPos().x, i->getPos().y, i->getSize().x, i->getSize().y, nonePen, *ballBrush));
        group_blocks->childItems()[group_blocks->childItems().size()-1]->setZValue(10);
    }
}

void gWindow::redrawPlatform()
{
    for(auto i : group_plate->childItems())
    {
        scene->removeItem(i);
    }
    group_plate->addToGroup(scene->addRect(0, 0, this->platf->getSize().x, this->platf->getSize().y, nonePen));
    group_plate->addToGroup(scene->addRect(0, 0, this->platf->getSize().x + 40, this->platf->getSize().y + 40, nonePen,*plateBrush));
    QTransform tmpTransf = group_plate->childItems()[0]->transform();
    tmpTransf.scale(1,0.80);
    this->plateBrush->setTransform(tmpTransf);
    group_plate->childItems()[0]->setPos(this->platf->getPos().x, this->platf->getPos().y);
    group_plate->childItems()[1]->setPos(this->platf->getPos().x - 20, this->platf->getPos().y - 20);
    group_blocks->childItems()[0]->setZValue(1);
    group_blocks->childItems()[1]->setFlag(QGraphicsItem::ItemNegativeZStacksBehindParent);
    group_blocks->childItems()[1]->setZValue(-5);
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
