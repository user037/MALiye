#include "player.h"

QRectF player::boundingRect() const
{

}

void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

int player::getCurScore()
{
    return this->curScore;
}

int player::getHighScore()
{
    return this->highScore;
}

int player::getHp()
{
    return this->hp;
}

int player::getStartHp()
{
    return this->startHp;
}

int player::getLevel()
{
    return this->level;
}

player::player(int curScore, int highScore, int hp, int startHp, int level, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->curScore = curScore;
    this->highScore = highScore;
    this->hp = hp;
    this->startHp = startHp;
    this->level = level;
}

void player::changeLevel(int newLevel)
{
    this->level = newLevel;
}

void player::setScore(int newScore)
{
    this->curScore = newScore;
}

void player::death()
{
    qDebug() << "ded :(";
    this->hp = this->startHp;
    this->highScore = std::max(this->highScore, this->curScore);
    this->curScore = 0;
}

void player::damage()
{
    --this->hp;
    if(this->hp == 0)
    {
        this->death();
    }
}


