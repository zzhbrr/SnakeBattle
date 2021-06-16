#include "playersnake.h"
#include "util.h"
#include "game.h"
extern Game *game;
extern bool PlayerAlive;

PlayerSnake::PlayerSnake(QGraphicsScene *scence, QString name, int leng): Snake(scence, name, leng) {
    // 默认朝向是向上
    direction = "up";
    typ = "player";
    PlayerAlive = true;

    // 设置蛇的图像
    int color = Util::Random(1, 10);
    pic = ":/images/picture/snakeUnit" + QString::number(color) + ".png";

    SnakeUnit *newunit = new SnakeUnit(this);
    newunit = new SnakeUnit(this);
    newunit->setPixmap(QPixmap(":/images/picture/snakeUnit" + QString::number(color) + "Head.png"));
    newunit->setTransformOriginPoint(newunit->pixmap().width()/2, newunit->pixmap().height()/2); // 将位图的中心点作为原点
    newunit->setPos(Util::screenWidth() / 2, Util::screenHeight() / 2); // 将蛇头置于中心位置
    newunit->setZValue(-2);
    scence->addItem(newunit);
    body.append(newunit);

    for (int i = 1; i <= length; i ++) {
        newunit = new SnakeUnit(this);
        newunit->setPixmap(":/images/picture/snakeUnit" + QString::number(color) + ".png");
        newunit->setZValue(-5); // 将身体z坐标置于头之下，头可以覆盖身体
        newunit->setPos(body[0]->x(), body[0]->y() + i * size);
        scence->addItem(newunit);
        body.append(newunit);
    }


    // 设置蛇的名字的位置，并显示
    SnakeNameText->setPos(body[0]->x(), body[0]->y()-10);
    scence->addItem(SnakeNameText);
}
