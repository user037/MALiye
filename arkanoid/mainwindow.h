#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <QObject>
#include <QTimer>
#include <platform.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *tmr;
    platform *platf;
public slots:
    void theDamnLoop();
signals:
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
