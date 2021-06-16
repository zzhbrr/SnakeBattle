#include "aisnake1.h"
#include "util.h"
#include "game.h"
#include <QChar>

extern Game *game;

AiSnake_1::AiSnake_1(QGraphicsScene *scence, QString name, int len, int X, int Y, QString dir): Snake(scence, name, len) {
    direction = dir;
    typ = "ai1";

    if (name == ".") {
        name.clear();
        // 设置一个随机名字
        int namelength = Util::Random(3, 4);
        for (int i = 1; i <= namelength; i ++) {
            if (i == 1) name.append(QChar(Util::Random('A', 'Z')));
            else name.append(QChar(Util::Random('a', 'z')));
        }
        name += "__easy";
    }

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

    // 设置Ai_1随机转变方向的时间
    ChangeDirectionTimer = new QTimer();
    connect(ChangeDirectionTimer, &QTimer::timeout, this, &AiSnake_1::RandomChangeDirection);
    ChangeDirectionTimer->start(1000); // 每行进1s换一次方向
}

void AiSnake_1::RandomChangeDirection() {
    int opt = Util::Random(1, 4);
    if (opt == 1) direction = "right";
    else if (opt == 2) direction = "left";
    else if (opt == 3) direction = "up";
    else direction = "down";
}

// 很多模块设计的不够合理
// 代码冗长、复用率不高
