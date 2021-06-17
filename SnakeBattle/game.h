#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <qstring.h>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>
#include <QString>
#include <QList>
#include <QMessageBox>

#include "util.h"
#include "normalfood.h"
#include "specialfood.h"
#include "deadfood.h"
#include "playersnake.h"
#include "snake.h"
#include "aisnake1.h"
#include "aisnake2.h"
#include "clocks.h"
#include "rankboard.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    QGraphicsScene *game_scence;

public:
    Game();
    Game(QString user_name, int Ai_1_num, int Ai_2_num);
    QString PlayerName;
    PlayerSnake *player;
    QMessageBox *Result;
    Clocks *ccl;
    void keyPressEvent(QKeyEvent *event);
    void GenerateAiSnakes(int num1, int num2);


public slots:
    void GenerateFood();
    void GenerateANewSnake();
    void GameEnd();
    void DeleteResult();
};

#endif // GAME_H

// 不知道如何让槽函数带参数
