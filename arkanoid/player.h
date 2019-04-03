#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <tools.h>

class player : public QGraphicsItem
{
public:
    int getHighScore();
    int getCurScore();
    int getHp();
    int getLevel();
    player(int highScore, int curScore, int hp, int level, QGraphicsItem *parent = nullptr);
    void changeLevel(int newLevel);
    void death();
    void damage();
private:
    int highScore;
    int curScore;
    int hp;
    int level;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // PLAYER_H
