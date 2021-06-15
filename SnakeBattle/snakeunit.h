#ifndef SNAKEUNIT_H
#define SNAKEUNIT_H
#include <QGraphicsPixmapItem>

class Snake;

class SnakeUnit: public QGraphicsPixmapItem
{
public:
    SnakeUnit(Snake *be);
    Snake *belong;
};

#endif // SNAKEUNIT_H
