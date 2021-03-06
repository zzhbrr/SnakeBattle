#include "normalfood.h"
#include "game.h"
#include "util.h"

NormalFood::NormalFood(QGraphicsScene *scence, int X, int Y): Items(scence, X, Y) {
    //添加图像
    setPixmap(QPixmap(":/images/picture/nmf"+ QString::number(Util::Random(1,5)) + ".png"));
    setPos(Util::Random(10,Util::screenWidth() - 10), Util::Random(10,Util::screenHeight() - 10));

    //设置大小
    setScale(0.025);

    //将食物加入
    scence->addItem(this);

}
