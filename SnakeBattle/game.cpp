#include "game.h"
#include <QDebug>
#include <QMessageBox>

extern bool HaveBegun;
extern bool BeginTheGame;
extern bool PlayerAlive;

Game::Game(){}
Game::Game(QString name, int Ai_1_num, int Ai_2_num) {

    // qDebug() << "in!!" << endl;

    // 将视图铺满整个屏幕
    setFixedHeight(Util::screenHeight());
    setFixedWidth(Util::screenWidth());

    // 创建新场景，并铺满整个屏幕
    game_scence = new QGraphicsScene(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // scroll bar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // scroll bar
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

    BeginTheGame = true;

    // 生成玩家控制的蛇
    PlayerName = name;
    player = new PlayerSnake(game_scence, name, 6);
    PlayerAlive = true;

    // 生成Ai蛇
    GenerateAiSnakes(Ai_1_num, Ai_2_num);

    // 生成排名表
    new RankBoard(game_scence);

    // 按规定时间加入食物
    QTimer *AddFoodTimer = new QTimer();
    connect(AddFoodTimer, SIGNAL(timeout()), this, SLOT(GenerateFood()));
    AddFoodTimer->start(200);

    // 生成倒计时时钟
    ccl = new Clocks(game_scence);
//    connect(ccl, &Clocks::TimeOutt, this, &Game::GameEnd);
}

void Game::GenerateFood() {
    // new SpecialFood(game_scence, Util::Random(10, Util::screenWidth()-10), Util::Random(10, Util::screenHeight()-10));
    if (!BeginTheGame or (BeginTheGame and HaveBegun)) {
        int opt = Util::Random(1, 15);
        if (opt <= 14) {
            new NormalFood(game_scence, 233, 233);
        } else if (opt == 15) {
            new DeadFood(game_scence, 233, 233);
        }
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) this->close(), HaveBegun = false;
    if (!HaveBegun) {
        if (event->key() == Qt::Key_Space) HaveBegun = true;
    } else {
        if (event->key() == Qt::Key_Space) HaveBegun = false;
        if (event->key() == Qt::Key_Up) player->ChangeDirection("up");
        if (event->key() == Qt::Key_Right) player->ChangeDirection("right");
        if (event->key() == Qt::Key_Left) player->ChangeDirection("left");
        if (event->key() == Qt::Key_Down) player->ChangeDirection("down");
        if (event->key() == Qt::Key_Shift) player->speed = 11;
        if (event->key() == Qt::Key_Control) player->speed = 8;
    }
}

void Game::GenerateAiSnakes(int num1, int num2) {
    // 生成num1只简单蛇
    for (int i = 1; i <= num1; i ++) {
        int opt = Util::Random(1, 4);
        if (opt == 1) new AiSnake_1(game_scence, ".", 6, 200, Util::Random(200, Util::screenHeight() - 200), "right"); // 生成在左边
        else if (opt == 2) new AiSnake_1(game_scence, ".", 6, Util::screenWidth() - 200, Util::Random(200, Util::screenHeight() - 200), "left"); // 生成在右边
        else if (opt == 3) new AiSnake_1(game_scence, ".", 6, Util::Random(200, Util::screenWidth() - 200), 200, "down"); // 生成在上边
        else new AiSnake_1(game_scence, ".", 6, Util::Random(200, Util::screenWidth() - 200), Util::screenHeight() - 200, "up"); // 生成在下边
    }
    // 生成num2只困难蛇
    for (int i = 1; i <= num2; i ++) {
        int opt = Util::Random(1, 4);
        if (opt == 1) new AiSnake_2(game_scence, ".", 6, 200, Util::Random(200, Util::screenHeight() - 200), "right"); // 生成在左边
        else if (opt == 2) new AiSnake_2(game_scence, ".", 6, Util::screenWidth() - 200, Util::Random(200, Util::screenHeight() - 200), "left"); // 生成在右边
        else if (opt == 3) new AiSnake_2(game_scence, ".", 6, Util::Random(200, Util::screenWidth() - 200), 200, "down"); // 生成在上边
        else new AiSnake_2(game_scence, ".", 6, Util::Random(200, Util::screenWidth() - 200), Util::screenHeight() - 200, "up"); // 生成在下边
    }
}

void Game::GenerateANewSnake() {
    if (!PlayerAlive) {
        player = new PlayerSnake(game_scence, PlayerName, 6);
    } else {
        // 死亡后随机生成蛇，生成level_2的蛇的概率是1/4
        int opt = Util::Random(1, 4);
        if (opt == 1) new AiSnake_1(game_scence, ".", 6, 200, Util::Random(200, Util::screenHeight() - 200), "right"); // 生成在左边
        else if (opt == 2) new AiSnake_1(game_scence, ".", 6, Util::screenWidth() - 200, Util::Random(200, Util::screenHeight() - 200), "left"); // 生成在右边
        else if (opt == 3) new AiSnake_1(game_scence, ".", 6, Util::Random(200, Util::screenWidth() - 200), 200, "down"); // 生成在上边
        else new AiSnake_2(game_scence, ".", 6, Util::Random(200, Util::screenWidth() - 200), Util::screenHeight() - 200, "up"); // 生成在下边
    }
}

void Game::GameEnd() {
    ccl->Remaintime = 300;
    qDebug() << "GameEnd" << endl;
    Result = new QMessageBox(this);
    HaveBegun = false;
    Result->setText(tr("GameEnd"));
    Result->show();
    QTimer::singleShot(5000, this, &Game::DeleteResult);
}

void Game::DeleteResult() {
    delete Result;
    this->close();
}
