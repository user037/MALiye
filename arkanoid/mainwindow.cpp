#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->addBrick({0,0},{100,50});
    ui->graphicsView->addBrick({100,0},{100,50});
    ui->graphicsView->redrawBricks();
}

MainWindow::~MainWindow()
{
    delete ui;
}
