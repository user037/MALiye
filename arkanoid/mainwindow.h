#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
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
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
public slots:
    void theDamnLoop();
signals:
private:
    int plate_dir = 0;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
