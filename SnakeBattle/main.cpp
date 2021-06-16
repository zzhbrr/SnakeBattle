#include "mainscence.h"
#include <random>

#include <QApplication>

bool HaveBegun = false;
bool BeginTheGame = false;
bool PlayerAlive = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainScence w;
    w.show();
    return a.exec();
}
