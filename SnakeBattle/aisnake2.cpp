#include "aisnake2.h"
#include "util.h"
#include "game.h"
#include <QChar>
#include <QPair>
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <map>
#include <vector>
using namespace std;

extern Game *game;
extern QGraphicsScene *Sce;

AiSnake_2::AiSnake_2(QGraphicsScene *scence, QString name, int len, int X, int Y, QString dir): Snake(scence, name, len) {
    direction = dir;
    typ = "ai2";

    if (name == ".") {
        name.clear();
        // 设置一个随机名字
        int namelength = Util::Random(3, 4);
        for (int i = 1; i <= namelength; i ++) {
            if (i == 1) name.append(QChar(Util::Random('A', 'Z')));
            else name.append(QChar(Util::Random('a', 'z')));
        }
        name += "__hard";
    }

    SnakeName = name;

    SnakeName = name;


    // 设置蛇的图像
    int color = Util::Random(1, 10);
    pic = ":/images/picture/snakeUnit" + QString::number(color) + ".png";

    SnakeUnit *newunit = new SnakeUnit(this);
    newunit = new SnakeUnit(this);
    newunit->setPixmap(QPixmap(":/images/picture/snakeUnit" + QString::number(color) + "Head.png"));
    newunit->setTransformOriginPoint(newunit->pixmap().width()/2, newunit->pixmap().height()/2); // 将位图的中心点作为原点
    newunit->setPos(X, Y); // 将蛇头置于指定位置
    newunit->belong = this;
    scence->addItem(newunit);
    body.append(newunit);

    for (int i = 1; i <= length; i ++) {
        newunit = new SnakeUnit(this);
        newunit->setPixmap(":/images/picture/snakeUnit" + QString::number(color) + ".png");
        newunit->setZValue(-5); // 将身体z坐标置于头之下，头可以覆盖身体
        if (dir == "right") {
            newunit->setPos(body[0]->x() - i * size, body[0]->y());
        } else if (dir == "left") {
            newunit->setPos(body[0]->x() + i * size, body[0]->y());
        } else if (dir == "up") {
            newunit->setPos(body[0]->x(), body[0]->y() + i * size);
        } else {
            newunit->setPos(body[0]->x(), body[0]->y() - i * size);
        }
        scence->addItem(newunit);
        body.append(newunit);
    }


    // 重新设置蛇的名字的位置，并显示
    SnakeNameText->setFont(QFont("calibri", 9));
    SnakeNameText->setPlainText(name);
    SnakeNameText->setDefaultTextColor(Qt::black);
    SnakeNameText->setPos(body[0]->x(), body[0]->y()-10);
    scence->addItem(SnakeNameText);

    ChangeDirectionTimer = new QTimer();
    connect(ChangeDirectionTimer, &QTimer::timeout, this, &AiSnake_2::CarefullyChangeDirection);
    ChangeDirectionTimer->start(50); // 每0.05s决定一次方向
}

void AiSnake_2::CarefullyChangeDirection() {

    pair <double, int> threat[4];
    threat[0].first = 2333333, threat[0].second = 0;
    threat[1].first = 2333333, threat[1].second = 1;
    threat[2].first = 2333333, threat[2].second = 2;
    threat[3].first = 2333333, threat[3].second = 3;
    // 四个方向的威胁
    // 0:right, 1:left, 2:up, 3:down

    // 计算威胁
    QList <QGraphicsItem *> theitems = Sce->items(); // 取出所有的图元
    for (int i = 0; i < theitems.size(); i ++) {
        QGraphicsItem *e = theitems[i];
        if (typeid (*e) != typeid (SnakeUnit) and typeid (*e) != typeid (DeadFood)) continue;
        if (typeid (*e) == typeid (SnakeUnit) and ((SnakeUnit *)e)->belong == this) continue;
        if (sqrt(pow(e->x()-body[0]->x(), 2)+pow(e->y()-body[0]->y(), 2)) > 90) continue;
//        qDebug() << sqrt(pow(e->x()-body[0]->x(), 2)+pow(e->y()-body[0]->y(), 2)) << endl;
//        qDebug() << "find a threat item" << endl;
        if (abs(e->y() - body[0]->y()) <= 10) {
            if (e->x() >= body[0]->x()) threat[0].first = min(threat[0].first, abs(e->x() - body[0]->x()));
            if (e->x() <= body[0]->x()) threat[1].first = min(threat[1].first, abs(e->x() - body[0]->x()));
        }
        if (abs(e->x() - body[0]->x()) <= 10) {
            if (e->y() >= body[0]->y()) threat[3].first = min(threat[3].first, abs(e->y() - body[0]->y()));
            if (e->y() <= body[0]->y()) threat[2].first = min(threat[2].first, abs(e->y() - body[0]->y()));
        }
    }
    sort(threat, threat + 4);
    // 设置至多两个方向不能移动
    bool cantmove[4] = {0, 0, 0, 0};
    for (int i = 0; i <= 1; i ++) {
        if (threat[i].first >= 100) break;
        cantmove[threat[i].second] = 1;
    }

    if (direction == "right") cantmove[1] = 1;
    if (direction == "left") cantmove[0] = 1;
    if (direction == "up") cantmove[3] = 1;
    if (direction == "down") cantmove[2] = 1;


    pair<double, int> dis[4];
    dis[0].first = 2333333, dis[0].second = 0;
    dis[1].first = 2333333, dis[1].second = 1;
    dis[2].first = 2333333, dis[2].second = 2;
    dis[3].first = 2333333, dis[3].second = 3;

    QGraphicsItem *minitem = theitems[0];
    double mindis = 2333333.0;

    for (int i = 0; i < theitems.size(); i ++) {
        QGraphicsItem *e = theitems[i];
        if (typeid (*e) == typeid (NormalFood) or typeid (*e) == typeid (SpecialFood)) {
            double d = sqrt(pow(e->x()-body[0]->x(), 2)+pow(e->y()-body[0]->y(), 2));
            if (d < mindis) mindis = d, minitem = e;
        }
    }

    if (minitem->x() > body[0]->x()) dis[0].first = abs(minitem->x() - body[0]->x());
    if (minitem->x() < body[0]->x()) dis[1].first = abs(minitem->x() - body[0]->x());
    if (minitem->y() > body[0]->y()) dis[3].first = abs(minitem->y() - body[0]->y());
    if (minitem->y() < body[0]->y()) dis[2].first = abs(minitem->y() - body[0]->y());

    sort(dis, dis + 4);
    bool haveDecided = false;
    for (int i = 0; i < 4; i ++) {
        if (cantmove[dis[i].second]) continue;
        haveDecided = true;
        if (dis[i].second == 0) direction = "right";
        else if (dis[i].second == 1) direction = "left";
        else if (dis[i].second == 2) direction = "up";
        else direction = "down";
        if (dis[i].first <= speed) speedlimit = dis[i].first;
        break;
    }
//    qDebug() << threat[0].first << " " << threat[1].first << " " << threat[2].first << " " << threat[3].first << endl;
//    qDebug() << cantmove[0] << " " << cantmove[1] << " " << cantmove[2] << " " << cantmove[3] << endl;
//    qDebug() << dis[0].first << " " << dis[1].first << " " << dis[2].first << " " << dis[3].first << endl;
//    qDebug() << dis[0].second << " " << dis[1].second << " " << dis[2].second << " " << dis[3].second << endl;
//    qDebug() << direction << endl << endl;
}

// Ai_2蛇出现不停抖动的问题
// 原因是算法设计问题
// 最近的食物有且仅有一个，所以ai蛇会想方设法靠近食物，于是两个方向同时设法靠近就出现抖动问题
// 解决思路:
// 找到离它最近的一个，只走两个方向其中之一
// 哦我之前否定过这一做法
// 因为这样显然会使得蛇走的路线不是较优的
// 但为了解决更严重的抖动问题，只能这么做了
// 找到抖动问题根源了，蛇速度一定，不能使其正好对准食物
// 解决方案是新增一个变量speedlimit，用于当一步距离大于想要走的距离时候.

// ai蛇对有些情况躲避不敏感
// 原因是单纯的把每一个unit元到头的坐标绝对值当做危险度，而没有考虑相对位置
// 大错特错了

// 现在Ai_2蛇只有可能在突然前方出现新出生的蛇才会死亡....
// 它们无敌了
