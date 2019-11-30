#include "UI/mainwindow.h"
#include <QApplication>
#include "QDebug"
#include <QObject>
#include <QSound>
#include "gamemanager.h"
#include "UI/clientwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

      // Network game
//    PlayWindow * gameUI = new PlayWindow();
//    ClientWindow* clientUI = new ClientWindow(gameUI);
//    GameManager gameManagerNetwork(6,gameUI, clientUI);
//    clientUI->show();

    //local game
    QFontDatabase::addApplicationFont(":/fonts/PressStart2P-Regular.ttf");
    QSound *sound = new QSound(":sounds/487724__mattix__ticking-timer-10-sec.wav");
    sound->setLoops(QSound::Infinite);
    sound->play();

    PlayWindow * gameUI2 = new PlayWindow();
    GameManager gameManagerLocal(6,gameUI2);
    return a.exec();
}
