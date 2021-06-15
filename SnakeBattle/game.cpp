#include "game.h"
#include <QDebug>

extern bool HaveBegun;

Game::Game(){}
Game::Game(QString name) {

    qDebug() << "in!!" << endl;

    // 将视图铺满整个屏幕
    setFixedHeight(Util::screenHeight());
    setFixedWidth(Util::screenWidth());

    // 创建新场景，并铺满整个屏幕
    game_scence = new QGraphicsScene(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//scroll bar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //scroll bar
    setWindowFlags(Qt::FramelessWindowHint);
    game_scence->setSceneRect(0,0,Util::screenWidth() - 5,Util::screenHeight() - 5);
    setScene(game_scence);

    // 设置背景
    QGraphicsRectItem *back = new QGraphicsRectItem(-Util::screenWidth(), -Util::screenHeight(), 3*Util::screenWidth(), 3*Util::screenHeight());
    back->setZValue(-1000);
    back->setBrush(QBrush(QPixmap(":/images/picture/back.jpg")/*.scaled(Util::screenWidth(), Util::screenHeight(), Qt::KeepAspectRatio, Qt::SmoothTransformation)*/));
    game_scence->addItem(back);

    // 生成初始食物
    for (int i = 1; i <= 40; i ++) GenerateFood();

    // 生成玩家控制的蛇
    name = "zZhBr";
    player = new PlayerSnake(game_scence, name, 6);

    // 按规定时间加入食物
    QTimer *AddFoodTimer = new QTimer();
    connect(AddFoodTimer, SIGNAL(timeout()), this, SLOT(GenerateFood()));
    AddFoodTimer->start(200);
}

void Game::GenerateFood() {
    // new SpecialFood(game_scence, Util::Random(10, Util::screenWidth()-10), Util::Random(10, Util::screenHeight()-10));
    int opt = Util::Random(1, 15);
    if (opt <= 14) {
        new NormalFood(game_scence, 233, 233);
    } else if (opt == 15) {
        new DeadFood(game_scence, 233, 233);
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) delete this;
    if (!HaveBegun) {
        if (event->key() == Qt::Key_Space) HaveBegun = true;
    } else {
        if (event->key() == Qt::Key_Space) HaveBegun = false;
        if (event->key() == Qt::Key_Up) player->ChangeDirection("up");
        if (event->key() == Qt::Key_Right) player->ChangeDirection("right");
        if (event->key() == Qt::Key_Left) player->ChangeDirection("left");
        if (event->key() == Qt::Key_Down) player->ChangeDirection("down");
        if (event->key() == Qt::Key_Shift) player->speed = 12;
        if (event->key() == Qt::Key_Control) player->speed = 5;
    }
}
