#include "UI/mainwindow.h"
#include <QApplication>
#include "QDebug"
#include <QObject>
#include "gamemanager.h"
#include "UI/clientwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

      // Network game
    PlayWindow * gameUI = new PlayWindow();
    ClientWindow* clientUI = new ClientWindow(gameUI);
    GameManager gameManagerNetwork(6,gameUI, clientUI);
    clientUI->show();

    //local game
//    PlayWindow * gameUI2 = new PlayWindow();
//    GameManager gameManagerLocal(6,gameUI2);

   return a.exec();
}

