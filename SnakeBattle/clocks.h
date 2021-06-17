#ifndef CLOCK_H
#define CLOCK_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Clocks: public QObject
{
//    Q_OBJECT
public:
    Clocks(QGraphicsScene *Scenc);
    QGraphicsScene *Sce;
    int Remaintime;
    int LastTime;
    QGraphicsTextItem *TimeText;

public slots:
    void ChangeTime();
signals:
    void TimeOutt();
};

#endif // CLOCK_H
