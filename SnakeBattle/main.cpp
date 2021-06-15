#include "mainscence.h"
#include <random>

#include <QApplication>

bool HaveBegun = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainScence w;
    w.show();
    return a.exec();
}
