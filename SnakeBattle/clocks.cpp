#include "clocks.h"
#include <QTimer>
#include <ctime>
#include <QString>
#include <QDebug>
#include "util.h"
#include "game.h"
extern Game* game;

Clocks::Clocks(QGraphicsScene *Scence)
{
    Sce = Scence;
    Remaintime = 300;
    LastTime = -1;
    QTimer *counttimer = new QTimer();
    connect(counttimer, &QTimer::timeout, this, &Clocks::ChangeTime);
    counttimer->start(500);
    TimeText = new QGraphicsTextItem();
    TimeText->setPlainText(tr("5:00"));
    TimeText->setPos(Util::screenWidth() / 2, 10);
    Scence->addItem(TimeText);
}

void Clocks::ChangeTime() {
    if (LastTime == -1) LastTime = time(NULL);
    if (time(NULL) != LastTime) {
        LastTime = time(NULL);
        Remaintime--;
        int min = Remaintime / 60, s = Remaintime % 60;
        QString text;
        if (s < 10)
            text = QString::number(min) + QString(" : 0") + QString::number(s);
        else text = QString::number(min) + QString(" : ") + QString::number(s);
        TimeText->setPlainText(text);
//        qDebug() << "changetime" << endl;
    }

    if (Remaintime < 0) {
//        qDebug() << "timeout!!!" << endl;
//        emit TimeOutt();
        // 不会用信号函数.....
        game->GameEnd();
    }
}

void Clocks::TimeOutt() {

}
