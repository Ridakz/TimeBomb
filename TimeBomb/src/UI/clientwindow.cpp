#include "UI/clientwindow.h"

ClientWindow::ClientWindow(PlayWindow* p) : m_pw(p)
{
    setupUi(this);
    m_socket = new QTcpSocket(this);

    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(readReceivedData()));
    QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(connect()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
}

void ClientWindow::on_connectButton_clicked()
{
    messageList->append(tr("<em>Trying to connect</em>"));
    connectButton->setEnabled(false);
    m_socket->abort();
    m_socket->connectToHost(serverIP->text(), serverPort->value());
}

void ClientWindow::sendMove(int playerId, int cardId)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (int) playerId << (int) cardId << (int) -1;
    m_socket->write(paquet);
}

void ClientWindow::sendCursorPosition(int x, int y)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (int) -1 << (int) x << (int) y;
    m_socket->write(paquet);
}

void ClientWindow::readReceivedData()
{
    QDataStream in(m_socket);

    if (m_socket->bytesAvailable() < (int)(3*sizeof(int)))
        return;

    int a,b,c;
    in >> a;
    in >> b;
    in >> c;

    QString receivedMsg = "Rcv " + QString::number(a)  + " " + QString::number(b) + " " + QString::number(c) ;
    messageList->append(receivedMsg);

    if(c == -1) {
        emit receivedMove(Move{a,b});
    }
    else if (a == -1) {
        emit receivedCursorPos(b,c);
    }
    else{
        emit receivedSizeAndIndex(static_cast<unsigned int>(a),b,c);
    }
}

void ClientWindow::connect()
{
    messageList->append(tr("<em>Connection successful !</em>"));
    connectButton->setEnabled(true);
}


void ClientWindow::disconnect()
{
    messageList->append(tr("<em>Disconnect from server</em>"));
}


void ClientWindow::socketError(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            messageList->append(tr("<em>ERREUR : le serveur n'a pas pu etre trouve. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            messageList->append(tr("<em>ERREUR : le serveur a refuse la connexion. Vérifiez si le programme \"serveur\" a bien ete lancé. Verifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            messageList->append(tr("<em>ERREUR : le serveur a coupe la connexion.</em>"));
            break;
        default:
            messageList->append(tr("<em>ERREUR : ") + m_socket->errorString() + tr("</em>"));
    }

    connectButton->setEnabled(true);
}

ClientWindow::~ClientWindow(){

}
