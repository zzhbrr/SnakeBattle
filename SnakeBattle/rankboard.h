#ifndef RANKBOARD_H
#define RANKBOARD_H
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QString>
#include <QTimer>
#include <QVector>
#include "game.h"

class RankBoard: public QObject
{
public:
    RankBoard(QGraphicsScene *Scenc);
    QGraphicsTextItem *Board;
    QGraphicsScene *sce;
    static bool cmp(Snake*A, Snake*B);
public slots:
    void UpdateBoard();
};

#endif // RANKBOARD_H
