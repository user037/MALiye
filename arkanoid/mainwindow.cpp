#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            ui->graphicsView->addBrick({105*i,55*j},{100,50});
        }
    }
    ui->graphicsView->redrawBricks();
    tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(theDamnLoop()));
    qDebug() << "Sent Signal!";
    tmr->setInterval(100);
    tmr->start();
    qDebug() << "Right NoW!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::theDamnLoop()
{
    for(int i = 0; i < ui->graphicsView->bricksCount(); i++)
        ui->graphicsView->getBrick(i)->setPos({ui->graphicsView->getBrick(i)->getPos().x + 5,ui->graphicsView->getBrick(i)->getPos().y});
    ui->graphicsView->redrawBricks();
}
