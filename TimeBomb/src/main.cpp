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
    ClientWindow* clientUI = new ClientWindow();
    GameManager gameManagerNetwork(clientUI);
    clientUI->show();

    //local game
//    PlayWindow * gameUI2 = new PlayWindow();
//    GameManager gameManagerLocal(6,gameUI2);

   return a.exec();
}

