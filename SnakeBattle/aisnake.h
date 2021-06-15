#ifndef AISNAKE_H
#define AISNAKE_H
#include "snake.h"

class AiSnake: public Snake
{
public:
    AiSnake(QGraphicsScene *scence, QString name, int leng, int typ, int X, int T, QString dir);
};

#endif // AISNAKE_H
