#include "rankboard.h"
#include <QGraphicsItem>
#include <vector>
#include <QList>
#include <QMap>
#include <algorithm>
#include <QtDebug>
#include "snakeunit.h"
#include "snake.h"
using namespace std;

RankBoard::RankBoard(QGraphicsScene *Scenc)
{
    sce = Scenc;
    // 设置排行榜
    Board = new QGraphicsTextItem();
    Board->setPos(20, 20);
    Board->setFont(QFont("calibri", 10));
    Board->setZValue(3); // 置于最顶层
    Scenc->addItem(Board);

    QTimer *UpdateBoardTimer = new QTimer();
    connect(UpdateBoardTimer, &QTimer::timeout, this, &RankBoard::UpdateBoard);
    UpdateBoardTimer->start(1000);
}

void RankBoard::UpdateBoard() {
    // 先取出所有的蛇
    QList <QGraphicsItem *> theitems = sce->items();
    vector <Snake*> snakes;
    QMap<Snake*, bool> Have;

    for (int i = 0; i < theitems.size(); i ++) {
        if (typeid (*theitems[i]) == typeid (SnakeUnit)) {
            Snake *thissnake = ((SnakeUnit *)theitems[i])->belong;
            if (!Have[thissnake]) {
                //qDebug() << thissnake->SnakeName << endl;
                Have[thissnake] = 1;
                snakes.push_back(thissnake);
            }
        }
    }
    // 对蛇的分数排序
    sort(snakes.begin(), snakes.end(), cmp);
    // 生成文本
    QString text = "Ranklist\n";
    for (int i = 0; i < (int)snakes.size(); i ++) {
        text += "#" + QString::number(i + 1) + QString("  ") + snakes[i]->SnakeName + QString("  ") + QString::number(snakes[i]->score) + " \n";
    }
    Board->setPlainText(text);
}

bool RankBoard::cmp(Snake*A, Snake*B) {
    return A->score > B->score;
}
