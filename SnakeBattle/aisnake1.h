#ifndef AISNAKE1_H
#define AISNAKE1_H
#include "snake.h"

class AiSnake_1: public Snake
{
public:
    AiSnake_1(QGraphicsScene *scence, QString name, int leng, int X, int Y, QString dir);
    QTimer *ChangeDirectionTimer;

public slots:
    void RandomChangeDirection();
};

#endif // AISNAKE_H

// Ai蛇的设计思路：
// level_1 随机变换方向
// level_2 会找最近的食物吃，并做避害
// 遗憾的是不会设计蛇让它有攻击欲望
