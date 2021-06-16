#ifndef AISNAKE2_H
#define AISNAKE2_H
#include "snake.h"

class AiSnake_2: public Snake
{
public:
    AiSnake_2(QGraphicsScene *scence, QString name, int leng, int X, int Y, QString dir);
    QTimer *ChangeDirectionTimer;

public slots:
    void CarefullyChangeDirection();
};


#endif // AISNAKE2_H
