#-------------------------------------------------
#
# Project created by QtCreator 2019-11-10T15:29:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = TimeBomb
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += $$PWD/include/

SOURCES += \
    src/Model/card.cpp \
    src/Model/cardgame.cpp \
    src/Model/deck.cpp \
    src/UI/clientwindow.cpp \
    src/UI/playercard.cpp \
    src/UI/playwindow.cpp \
    src/botplayer.cpp \
    src/gamemanager.cpp \
    src/humanplayer.cpp \
    src/main.cpp \
    src/player.cpp \
    src/server.cpp


HEADERS += \
    include/Model/card.h \
    include/Model/cardgame.h \
    include/Model/deck.h \
    include/Model/move.h \
    include/Model/side.h \
    include/UI/clientwindow.h \
    include/UI/playercard.h \
    include/UI/playwindow.h \
    include/UI/ui_client.h \
    include/botplayer.h \
    include/gamemanager.h \
    include/humanplayer.h \
    include/player.h \
    include/server.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
