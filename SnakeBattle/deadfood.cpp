#include "deadfood.h"
#include "util.h"
#include "game.h"

DeadFood::DeadFood(QGraphicsScene *scence, int X, int Y): Items(scence, X, Y) {
    //添加图像
    setPixmap(QPixmap(":/images/picture/stone.png"));
    setPos(Util::Random(10,Util::screenWidth() - 10), Util::Random(10,Util::screenHeight() - 10));

    //设置大小
    setScale(1.5);

    //将食物加入
    scence->addItem(this);
}
