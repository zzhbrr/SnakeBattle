#ifndef PLAYERSNAKE_H
#define PLAYERSNAKE_H
#include "snake.h"


class PlayerSnake: public Snake
{
public:
    PlayerSnake(QGraphicsScene *scence, QString name, int leng);
};

#endif // PLAYERSNAKE_H
