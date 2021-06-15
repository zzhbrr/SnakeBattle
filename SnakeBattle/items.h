#ifndef ITEMS_H
#define ITEMS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Items : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Items(QGraphicsScene *scence, int X, int Y);
    int life;

public slots:
    void DecreaseLife();

};

#endif // ITEMS_H
