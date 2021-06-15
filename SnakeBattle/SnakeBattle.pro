QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Items.cpp \
    aisnake.cpp \
    deadfood.cpp \
    game.cpp \
    main.cpp \
    mainscence.cpp \
    normalfood.cpp \
    playersnake.cpp \
    snake.cpp \
    snakeunit.cpp \
    specialfood.cpp \
    util.cpp

HEADERS += \
    Items.h \
    aisnake.h \
    deadfood.h \
    game.h \
    mainscence.h \
    normalfood.h \
    playersnake.h \
    snake.h \
    snakeunit.h \
    specialfood.h \
    util.h

FORMS += \
    mainscence.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
