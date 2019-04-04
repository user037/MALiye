#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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
    ui->graphicsView->addBall({500,500},{50,50},{-2,-2});
    for(int i = 1; i <= 6; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            ui->graphicsView->addBrick({105*i-25,55*j},{100,50}, 1);
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

void MainWindow::theDamnLoop()
{
    //for(int i = 0; i < ui->graphicsView->bricksCount(); i++)
    //ui->graphicsView->getBrick(i)->setPos({ui->graphicsView->getBrick(i)->getPos().x + 5,ui->graphicsView->getBrick(i)->getPos().y});
    ui->graphicsView->platf->move(plate_dir);
    for(int i = 0; i < ui->graphicsView->ballsCount(); i++)
    {
        int collided = 0; //0 - no collision, 1 - top/bottom, 2 - right/left
        ball *b = ui->graphicsView->getBall(i);
        const float delta = 0.01;
        for(int j; j < ui->graphicsView->bricksCount(); j++)
        {
            if(fabs(b->getPos().y - (ui->graphicsView->getBrick(j)->getPos().y + 50)) < delta)
            {
                collided = 1;
            }
            if(fabs((b->getPos().y + 50) - ui->graphicsView->getBrick(j)->getPos().x) < delta)
            {
                collided = 1;
            }
            if(fabs(b->getPos().x - (ui->graphicsView->getBrick(j)->getPos().x + 100)) < delta)
            {
                collided = 2;
            }
            if(fabs((b->getPos().x + 50) - ui->graphicsView->getBrick(j)->getPos().x) < delta)
            {
                collided = 2;
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
        b->move();
    }
    ui->graphicsView->totalRedraw();
}
