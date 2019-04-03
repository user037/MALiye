#include "player.h"

QRectF player::boundingRect() const
{

}

void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

int player::getHighScore()
{
    return this->highScore;
}

int player::getCurScore()
{
    return this->curScore;
}

int player::getHp()
{
    return this->hp;
}

int player::getLevel()
{
    return this->level;
}

void player::death()
{

}

void player::damage()
{
    --this->hp;
    if(hp == 0)
    {
        this->death();
    }
}
