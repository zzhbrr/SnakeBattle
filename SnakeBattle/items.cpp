#include "Items.h"
#include "game.h"
#include "util.h"

//注意一定要写extern!!!表明是以前声明过的!!!
extern Game *game;

Items::Items(QGraphicsScene *scence, int X, int Y) {

    //置于最底层
    setZValue(-10);

    //设置寿命
    life = Util::Random(30, 35);

    //计时 每到规定时间存在时间-1
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(DecreaseLife()));
    timer->start(1000);
}

void Items::DecreaseLife() {
    life--;
    if (life == 0) {
        game->scene()->removeItem(this);
        delete this;
    }
}
