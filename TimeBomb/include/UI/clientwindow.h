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
        ClientWindow(PlayWindow * p);
        virtual ~ClientWindow();
        signals:
        void receivedMove(Move move);
        void receivedSizeAndIndex(unsigned int seed, int playerCount, int index);

    public slots:
        void sendMove(int playerId, int cardId);
        void on_connectButton_clicked();
        void donneesRecues();
        void connect();
        void disconnect();
        void socketError(QAbstractSocket::SocketError erreur);

    public:
        QTcpSocket *m_socket;
        PlayWindow* m_pw;
};
#endif // CLIENTWINDOWW_H
