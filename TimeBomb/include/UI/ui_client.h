#ifndef UI_CLIENT_H
#define UI_CLIENT_H

/********************************************************************************
** Form generated from reading UI file 'FenClient.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENCLIENT_H
#define UI_FENCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenClient
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *serverIP;
    QLabel *label_2;
    QSpinBox *serverPort;
    QPushButton *connectButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *messageList;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *FenClient)
    {
        if (FenClient->objectName().isEmpty())
            FenClient->setObjectName(QString::fromUtf8("FenClient"));
        FenClient->resize(628, 292);
        QIcon icon;
        icon.addFile(QString::fromUtf8("chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        FenClient->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(FenClient);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FenClient);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        serverIP = new QLineEdit(FenClient);
        serverIP->setObjectName(QString::fromUtf8("serveurIP"));
        serverIP->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(serverIP);

        label_2 = new QLabel(FenClient);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        serverPort = new QSpinBox(FenClient);
        serverPort->setObjectName(QString::fromUtf8("serveurPort"));
        serverPort->setMinimumSize(QSize(60, 0));
        serverPort->setMinimum(1024);
        serverPort->setMaximum(65535);
        serverPort->setValue(16000);

        horizontalLayout->addWidget(serverPort);

        connectButton = new QPushButton(FenClient);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout->addWidget(connectButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(FenClient);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setPixmap(QPixmap(QString::fromUtf8("chat.png")));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(FenClient);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        messageList = new QTextEdit(FenClient);
        messageList->setObjectName(QString::fromUtf8("listeMessages"));
        messageList->setReadOnly(true);

        verticalLayout_2->addWidget(messageList);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(FenClient);

        QMetaObject::connectSlotsByName(FenClient);
    } // setupUi

    void retranslateUi(QWidget *FenClient)
    {
        FenClient->setWindowTitle(QCoreApplication::translate("FenClient", "ZeroChat - Client", nullptr));
        label->setText(QCoreApplication::translate("FenClient", "IP du serveur :", nullptr));
        serverIP->setText(QCoreApplication::translate("FenClient", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("FenClient", "Port du serveur :", nullptr));
        connectButton->setText(QCoreApplication::translate("FenClient", "Connexion", nullptr));
        label_6->setText(QCoreApplication::translate("FenClient", "ZeroChat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FenClient: public Ui_FenClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENCLIENT_H


#endif // UI_CLIENT_H
