#ifndef SNAKE_H
#define SNAKE_H
#include<QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QGraphicsTextItem>
#include <QString>
#include <QPair>
#include <QTimer>
#include "snakeunit.h"

class Snake: public QObject
{
    //Q_OBJECT
public:
    Snake(QGraphicsScene *scence, QString name, int leng);
    bool alive; // 是否存活
    int length; // 蛇的长度
    int score; // 蛇的分数
    int size; // 蛇的大小
    int speed; // 蛇的速度
    int speedlimit; // 可以让Ai蛇对准食物
    int foodcount; // 吃的食物的数量，每吃3个食物score+1
    QString typ; // 蛇的类型Ai/Player
    //QList<QPair<QGraphicsPixmapItem*, Snake*> > body; // 存储蛇的身体单元
    QList<SnakeUnit *> body; // 存储蛇的身体单元
    QGraphicsTextItem *SnakeNameText; // 显示蛇的名字的元
    QString SnakeName; // 蛇的名字
    QString direction; // 蛇头的方向
    QString pic; // 蛇身体图像的路径名字
    QGraphicsEllipseItem *boundary; // 蛇头的碰撞区域
    QTimer *SnakeMoveTimer; // 蛇移动的计时器
    void AppendNewUnit();
    void DestroySnake();
    void ChangeDirection(QString dir); // 改变头部图像的方向


public slots:
    void Move();
};

#endif // SNAKE_H

// 定义类的时候没有写Q_OBJECT
// 抛出No such slot错误
