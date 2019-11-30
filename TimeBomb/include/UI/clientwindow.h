#ifndef CLIENTWINDOWW_H
#define CLIENTWINDOWW_H

#include <QtGui>
#include <QtNetwork>
#include "ui_client.h"
#include "playwindow.h"


class ClientWindow : public QWidget, private Ui_FenClient
{
    Q_OBJECT

    public:
        ClientWindow();
        virtual ~ClientWindow();

   signals:
        void receivedMove(Move move);
        void receivedSizeAndIndex(unsigned int seed, int playerCount, int index);
        void receivedCursorPos(int x, int y);

    public slots:
        void sendMove(int playerId, int cardId);
        void sendCursorPosition(int x, int y);
        void on_connectButton_clicked();
        void readReceivedData();
        void connect();
        void disconnect();
        void socketError(QAbstractSocket::SocketError erreur);

    public:
        QTcpSocket *m_socket;
};
#endif // CLIENTWINDOWW_H
