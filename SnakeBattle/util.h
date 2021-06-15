#ifndef UTIL_H
#define UTIL_H
#include <QDesktopWidget>

class Util
{
public:
    Util();
    static int screenWidth();
    static int screenHeight();
    static int Random(int x, int y);
};

#endif // UTIL_H
