#include "util.h"

Util::Util(){}

int Util::screenWidth() {
    QDesktopWidget widget;
    return widget.screenGeometry(-1).width();
}

int Util::screenHeight() {
    QDesktopWidget widget;
    return widget.screenGeometry(-1).height();
}

int Util::Random(int x, int y) {
    return rand() % (y - x + 1) + x;
}
