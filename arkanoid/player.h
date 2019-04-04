#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QDebug>
#include <tools.h>

class player : QGraphicsItem
{
public:
    int getCurScore();
    int getHighScore();
    int getHp();
    int getStartHp();
    int getLevel();
    player(int curScore, int highScore, int hp, int startHp, int level, QGraphicsItem *parent = nullptr);
    void changeLevel(int newLevel);
    void death();
    void damage();
private:
    int curScore;
    int highScore;
    int hp;
    int startHp;
    int level;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // PLAYER_H
