#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::mainLoop()
{

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
