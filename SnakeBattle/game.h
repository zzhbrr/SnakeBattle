#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <qstring.h>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>

#include "util.h"
#include "normalfood.h"
#include "specialfood.h"
#include "deadfood.h"
#include "playersnake.h"
#include "aisnake.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    QGraphicsScene *game_scence;

public:
    Game();
    Game(QString user_name);
    PlayerSnake *player;
    void keyPressEvent(QKeyEvent *event);

public slots:
    void GenerateFood();
};

#endif // GAME_H
