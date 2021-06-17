#include "deadfood.h"
#include "util.h"
#include "game.h"

DeadFood::DeadFood(QGraphicsScene *scence, int X, int Y): Items(scence, X, Y) {
    // 添加图像
    setPixmap(QPixmap(":/images/picture/ddf.png"));
    setPos(Util::Random(10,Util::screenWidth() - 10), Util::Random(10,Util::screenHeight() - 10));

    // 把石头设在最上方防止被食物挡住
    setZValue(10000);

    // 设置大小
    setScale(0.1);

    // 将食物加入
    scence->addItem(this);
}
