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

int player::getLevel()
{
    return this->level;
}

player::player(int curScore, int highScore, int hp, int level, QWidget *widget)
{

}

void player::changeLevel(int newLevel)
{
    this->level = newLevel;
}

void player::death()
{

}

void player::damage()
{
    --this->hp;
    if(this->hp == 0)
    {
        this->death();
    }
}
