#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include <QTcpServer>
#include <QObject>
#include <QDebug>


class Server : public QObject
{
Q_OBJECT
public:

    Server() :  QObject() {
        socket = new QTcpSocket(this);

        socket->abort(); // On d�sactive les connexions pr�c�dentes s'il y en a
        //socket->connectToHost(serveurIP->text(), serveurPort->value()); // On se connecte au serveur demand�
        socket->connectToHost("127.0.0.1",50885);
        QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readMove()));
        QObject::connect(socket, SIGNAL(connected()), this, SLOT(connect()));
        QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorr(QAbstractSocket::SocketError)));

    }
    QTcpSocket *socket;



    void sendMove(int playerId, int cardId) {
        QByteArray paquet;
        QDataStream out(&paquet, QIODevice::WriteOnly);
        out << (int) playerId << (int) cardId;
        socket->write(paquet); // On envoie le paquet
    }

public slots:
   void readMove() {

       QDataStream in(socket);

       if (socket->bytesAvailable() < (int)(2*sizeof(int)))
           return;

       int a,b;
       in >> a;
       in >> b;

    }

   void connect() {
       qDebug()  << "CONNECTED SUCCESS";
   }

   void errorr(QAbstractSocket::SocketError erreur) {
       switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
       {
           case QAbstractSocket::HostNotFoundError:
               qDebug() << "<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>";
               break;
           case QAbstractSocket::ConnectionRefusedError:
               qDebug() <<"<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>";
               break;
           case QAbstractSocket::RemoteHostClosedError:
               qDebug() << "<em>ERREUR : le serveur a coupé la connexion.</em>";
               break;
           default:
               qDebug() << "<em>ERREUR : ";
       }

   }


};

#endif // SERVER_H
