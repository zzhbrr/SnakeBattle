#include "specialfood.h"
#include "game.h"
#include "util.h"

SpecialFood::SpecialFood(QGraphicsScene *scence, int X, int Y): Items(scence, X, Y) {
    //添加图像
    setPixmap(QPixmap(":/images/picture/spf"+ QString::number(Util::Random(1,4)) + ".png"));
    setPos(X, Y);

    //设置大小
    setScale(0.05);

    // 设置角度
    setRotation(Util::Random(-75, 75));

    //将食物加入
    scence->addItem(this);
}
