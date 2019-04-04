#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <platform.h>
#include <bits/stdc++.h>
#include <QDebug>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QTimer *tmr;
    platform *platf;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
public slots:
    void theDamnLoop();
signals:
private:
    int plate_dir = 0;
    QVector  <bool> keys;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
