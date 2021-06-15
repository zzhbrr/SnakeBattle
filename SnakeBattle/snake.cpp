#include "snake.h"
#include "util.h"
#include "game.h"
#include "specialfood.h"
#include <QDebug>

extern Game *game;
QGraphicsScene *Sce;
extern bool HaveBegun;

Snake::Snake(QGraphicsScene *scence, QString name, int leng) {
    Sce = scence;
    length = leng;
    SnakeName = name;
    score = 0;
    size = 6;
    speed = size + 2;
    foodcount = 0;
    alive = true;

    //蛇的名字
    SnakeNameText = new QGraphicsTextItem();
    SnakeNameText->setFont(QFont("calibri", 9));
    SnakeNameText->setPlainText(name);
    SnakeNameText->setDefaultTextColor(Qt::black);

    // 碰撞边界初始化
    boundary = new QGraphicsEllipseItem(0, 0, 14, 14);
    boundary->setPen(QPen(Qt::transparent)); // 把边界设置成透明的
    boundary->setZValue(-1);
    Sce->addItem(boundary);

    // 蛇的移动
    SnakeMoveTimer = new QTimer();
    connect(SnakeMoveTimer, &QTimer::timeout, this, &Snake::Move);
    SnakeMoveTimer->start(100); // 每计100次进行一次移动
}


void Snake::Move() {
    if (HaveBegun) {
        // 移动身体
        for (int i = body.size() - 1; i >= 1; i --) {
            body[i]->setX(body[i - 1]->x());
            body[i]->setY(body[i - 1]->y());
        }
        // 移动头
        if (direction == "right") {
             body[0]->setX(body[0]->x() + speed);
        } else if (direction == "left")  {
             body[0]->setX(body[0]->x() - speed);
        } else if (direction == "up") {
            body[0]->setY(body[0]->y() - speed);
        } else {
            body[0]->setY(body[0]->y() + speed);
        }

        // 移动头的判定区域
        boundary->setX(body[0]->x());
        boundary->setY(body[0]->y());

        // 移动蛇的名字
        SnakeNameText->setX(body[0]->x() + 10);
        SnakeNameText->setY(body[0]->y() + 10);

        // 检测碰撞事件

        QList<QGraphicsItem *> colliding_items = body[0]->collidingItems();
        for (int i = 0; i < colliding_items.size(); i ++) {
            // 碰撞的是正常食物
            if (typeid (*(colliding_items[i])) == typeid (NormalFood)) {
                // 清除食物元
                Sce->removeItem(colliding_items[i]);
                delete colliding_items[i];

                foodcount ++;
                if (foodcount >= 3) {
                    foodcount -= 3;
                    score ++;
                    AppendNewUnit();
                }
            } else if (typeid (*(colliding_items[i])) == typeid (SpecialFood)) {
                // 碰撞的是特殊食物
                // 清除食物元
                Sce->removeItem(colliding_items[i]);
                delete colliding_items[i];

                foodcount += 2;
                if (foodcount >= 5) {
                    foodcount -= 5;
                    score ++;
                    AppendNewUnit();
                }
            } else if (typeid (*(colliding_items[i])) == typeid (DeadFood)) {
                // 碰撞的是致死食物
                // 清除食物元
                Sce->removeItem(colliding_items[i]);
                delete colliding_items[i];
                DestroySnake();
                break; // 不用吃到其他食物
            } else if (typeid (*colliding_items[i]) == typeid (SnakeUnit)){ // 碰到的蛇的身体
                // 直接强制类型转换进行判定，巧妙
                if (((SnakeUnit *)colliding_items[i])->belong != this) { // 如果碰到的不是自己的身体
                    DestroySnake();
                    break; // 不用吃到其他食物
                }
            }
        }
    }
}

void Snake::AppendNewUnit() {
    SnakeUnit *newunit = new SnakeUnit(this);
    newunit->setPixmap(QPixmap(pic));
    newunit->setPos(-233, 233); // 把这个图像先设置在屏幕以外，等到下次蛇移动的时候，会自动加入到蛇的身体里
    Sce->addItem(newunit);
    newunit->belong = this;
    body.append(newunit);
}

void Snake::DestroySnake() {
    alive = false;
    // 删除蛇的名字以及所有蛇的图像，且都变成特殊食物
    Sce->removeItem(SnakeNameText);
    for (int i = 0; i < body.size(); i ++) {
        new SpecialFood(Sce, body[i]->x(), body[i]->y());
        Sce->removeItem(body[i]);
    }
    // 删除蛇的头部碰撞圆
    Sce->removeItem(boundary);
    delete this;
}

void Snake::ChangeDirection(QString dir) {
    if (dir == "right" and direction != 'left') { // 不能直接反向
        direction = "right";
        body[0]->setRotation(0); // 先变成正向
        body[0]->setRotation(90);
    } else if (dir == "left" and direction != "right") {
        direction = "left";
        body[0]->setRotation(0); // 先变成正向
        body[0]->setRotation(-90);
    } else if (dir == "up" and direction != "down") {
        direction = "up";
        body[0]->setRotation(0);
    } else if (dir == "down" and direction != "up") {
        direction = "down";
        body[0]->setRotation(0); // 先变成正向
        body[0]->setRotation(180);

    }

}

// 本来以为只用用个pair就能解决判断碰撞的是否是自己身体了
// 结果发现必须新建一个类
// 设置一个Q..Item的派生类，就可以强制判断了
// 重构代码
