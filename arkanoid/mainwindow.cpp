#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Arkanoid-3000.");

    ui->graphicsView->setFixedSize(800, 600);
    ui->graphicsView->setSceneRect(0, 0, 795, 595);
    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    for(int i  = 0; i < 256; i++)//init keys
    {
        keys.push_back(0);
    }
    ui->graphicsView->addBall({400,400},{50,50},{-1,-2});
    for(int i = 1; i <= 6; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            ui->graphicsView->addBrick({105.0*i-25,55.0*j},{100,50},1);
        }
    }
    ui->graphicsView->addPlatform();
    ui->graphicsView->redrawBricks();
    ui->graphicsView->redrawPlatform();
    tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(theDamnLoop()));
    qDebug() << "Sent Signal!";
    tmr->setInterval(15);
    tmr->start();
    qDebug() << "Right NoW!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat() == 0)
    {
        keys[e->nativeScanCode()] = 1;

        //press
        if(keys[38]) // Left
        {
            plate_dir = -1;
        }
        else if(keys[40])// Right
        {
            plate_dir = 1;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat() == 0)
    {
        keys[e->nativeScanCode()] = 0;
    }

    //release
    if(e->isAutoRepeat() == 0)
    {
        if(!keys[38] && !keys[40])
            plate_dir = 0;
        else {
            if(keys[38])// Right
            {
                plate_dir = -1;
            }
            else if(keys[40])// Right
            {
                plate_dir = 1;
            }
        }
    }
}

/*point intersecsion(point a, point b, point c, point d)
{
    double a1 = b.y - a.y, b1 = a.x - b.x, c1 = a.x * (a.y - b.y) + a.y * (b.x - a.x);
    double a2 = d.y - c.y, b2 = c.x - d.x, c2 = c.x * (c.y - d.y) + c.y * (d.x - c.x);
    point p;
    p.x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    p.y = (a1 * c2 - a2 * c1) / (b1 * a2 - b2 * a1);
    if(p.x < std::max(a.x, b.x) && p.x > std::min(a.x, b.x) && p.y < std::max(a.y, b.y) && p.y > std::min(a.y, b.y))
    {
       if(p.x < std::max(c.x, d.x) && p.x > std::min(c.x, d.x) && p.y < std::max(c.y, d.y) && p.y > std::min(c.y, d.y))
       {
           return p;
       }
    }
    return {-1, -1};

}*/

void MainWindow::theDamnLoop()
{
    //for(int i = 0; i < ui->graphicsView->bricksCount(); i++)
    //ui->graphicsView->getBrick(i)->setPos({ui->graphicsView->getBrick(i)->getPos().x + 5,ui->graphicsView->getBrick(i)->getPos().y});
    ui->graphicsView->platf->move(plate_dir);
    for(int i = 0; i < ui->graphicsView->ballsCount(); i++)
    {
        int collided = 0; //0 - no collision, 1 - top/bottom, 2 - right/left
        ball *b = ui->graphicsView->getBall(i);
        double delta = std::max(std::fabs(b->getVelocity().x), std::fabs(b->getVelocity().y));
        /*for(int j = 0; j < ui->graphicsView->bricksCount(); j++)
        {
            point p1 = ui->graphicsView->getBrick(j)->getPos();
            point p2 = {ui->graphicsView->getBrick(j)->getPos().x + 100, ui->graphicsView->getBrick(j)->getPos().y};
            point p3 = {ui->graphicsView->getBrick(j)->getPos().x, ui->graphicsView->getBrick(j)->getPos().y + 50};
            point p4 = {ui->graphicsView->getBrick(j)->getPos().x + 100, ui->graphicsView->getBrick(j)->getPos().y + 50};
            point destination = {b->getPos().x + b->getVelocity().x, b->getPos().y + b->getVelocity().y};
            point check = {-1, -1};
            if(fabs(intersecsion(b->getPos(), destination, p1, p2).x - check.x) > delta && fabs(intersecsion(b->getPos(), destination, p1, p2).y - check.y) > delta)
            {
                collided = 1;
                qDebug() << intersecsion(b->getPos(), destination, p2, p4).x - b->getPos().x << intersecsion(b->getPos(), destination, p2, p4).y - b->getPos().y;
                b->changeDir({intersecsion(b->getPos(), destination, p2, p4).x - b->getPos().x, intersecsion(b->getPos(), destination, p2, p4).y - b->getPos().y});
            }
            else if(fabs(intersecsion(b->getPos(), destination, p3, p4).x - check.x) > delta && fabs(intersecsion(b->getPos(), destination, p3, p4).y - check.y) > delta)
            {
                collided = 1;
                qDebug() << "2";
                b->changeDir({intersecsion(b->getPos(), destination, p2, p4).x - b->getPos().x, intersecsion(b->getPos(), destination, p2, p4).y - b->getPos().y});
            }
            else if(fabs(intersecsion(b->getPos(), destination, p1, p3).x - check.x) > delta && fabs(intersecsion(b->getPos(), destination, p1, p3).y - check.y) > delta)
            {
                collided = 2;
                qDebug() << "3";
                b->changeDir({intersecsion(b->getPos(), destination, p2, p4).x - b->getPos().x, intersecsion(b->getPos(), destination, p2, p4).y - b->getPos().y});
            }
            else if(fabs(intersecsion(b->getPos(), destination, p2, p4).x - check.x) > delta && fabs(intersecsion(b->getPos(), destination, p2, p4).y - check.y) > delta)
            {
                collided = 2;
                qDebug() << "4";
                b->changeDir({intersecsion(b->getPos(), destination, p2, p4).x - b->getPos().x, intersecsion(b->getPos(), destination, p2, p4).y - b->getPos().y});
            }
        }*/
        //b->move();
        for(int j = 0; j < ui->graphicsView->bricksCount(); j++)
        {
            if(ui->graphicsView->getBrick(j)->getId() == 0)
            {
                continue;
            }
            point p1 = {ui->graphicsView->getBrick(j)->getPos().x, ui->graphicsView->getBrick(j)->getPos().y};
            point p2 = {ui->graphicsView->getBrick(j)->getPos().x + ui->graphicsView->getBrick(j)->getSize().x, ui->graphicsView->getBrick(j)->getPos().y};
            point p3 = {ui->graphicsView->getBrick(j)->getPos().x, ui->graphicsView->getBrick(j)->getPos().y + ui->graphicsView->getBrick(j)->getSize().y};
            point p4 = {ui->graphicsView->getBrick(j)->getPos().x + ui->graphicsView->getBrick(j)->getSize().x, ui->graphicsView->getBrick(j)->getPos().y + ui->graphicsView->getBrick(j)->getSize().y};
            if(fabs(b->getPos().y + b->getSize().y - p1.y) < delta && b->getPos().x < p2.x && b->getPos().x + b->getSize().x > p1.x)
            {
                collided = 1;
                ui->graphicsView->getBrick(j)->hit();
                //break;
            }
            if(fabs(b->getPos().y - p3.y) < delta && b->getPos().x < p4.x && b->getPos().x + b->getSize().x > p3.x)
            {
                collided = 1;
                ui->graphicsView->getBrick(j)->hit();
                break;
            }
            if(fabs(b->getPos().x + b->getSize().x - p1.x) < delta && b->getPos().y < p3.y && b->getPos().y + b->getSize().y > p1.y)
            {
                collided = 2;
                ui->graphicsView->getBrick(j)->hit();
                break;
            }
            if(fabs(b->getPos().x - p2.x) < delta && b->getPos().y < p4.y && b->getPos().y + b->getSize().y > p2.y)
            {
                collided = 2;
                ui->graphicsView->getBrick(j)->hit();
                break;
            }
        }

        if(collided == 1)
        {
            b->changeDir({b->getVelocity().x, -b->getVelocity().y});
        }
        else if(collided == 2)
        {
            b->changeDir({-b->getVelocity().x, b->getVelocity().y});
        }
        int isInBound = ui->graphicsView->isBallInBound(b);
        if(isInBound == 1)
        {
            b->changeDir({-b->getVelocity().x, b->getVelocity().y});
        }
        if(isInBound == 2)
        {
            b->changeDir({b->getVelocity().x, -b->getVelocity().y});
        }
        if(isInBound == 3)
        {
            b->changeDir({-b->getVelocity().x, b->getVelocity().y});
        }
        if(isInBound == 4)
        {
            b->changeDir({b->getVelocity().x, -b->getVelocity().y});
        }
        if(fabs(b->getPos().y + 50 - ui->graphicsView->platf->getPos().y) < delta && b->getPos().x < ui->graphicsView->platf->getPos().x + 150 && b->getPos().x + 50 > ui->graphicsView->platf->getPos().x)
        {
            b->changeDir({b->getVelocity().x, -b->getVelocity().y});
        }
        b->move();
    }
    ui->graphicsView->totalRedraw();
}
