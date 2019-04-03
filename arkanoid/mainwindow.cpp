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

    for(int i = 1; i <= 6; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            ui->graphicsView->addBrick({105*i-25,55*j},{100,50}, 1);
        }
    }
    ui->graphicsView->addPlatform();
    ui->graphicsView->redrawBricks();
    ui->graphicsView->redrawPlate();
    tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(theDamnLoop()));
    qDebug() << "Sent Signal!";
    tmr->setInterval(25);
    tmr->start();
    qDebug() << "Right NoW!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    qDebug() << e;
    if(e->key() == Qt::Key_A)
        plate_dir = -1;
    if(e->key() == Qt::Key_D)
        plate_dir = 1;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_A || e->key() == Qt::Key_D)
        plate_dir = 0;
    qDebug() << e;
}

void MainWindow::theDamnLoop()
{
    //for(int i = 0; i < ui->graphicsView->bricksCount(); i++)
    //ui->graphicsView->getBrick(i)->setPos({ui->graphicsView->getBrick(i)->getPos().x + 5,ui->graphicsView->getBrick(i)->getPos().y});
    if(plate_dir == -1)
        ui->graphicsView->platf->move(0);
    if(plate_dir == 1)
        ui->graphicsView->platf->move(1);
    ui->graphicsView->totalRedraw();
}
