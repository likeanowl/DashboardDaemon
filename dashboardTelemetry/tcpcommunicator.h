#pragma once

#include "icommunicator.h"
#include "parser.h"

#include <QTcpSocket>
#include <QDataStream>

class TcpCommunicator : public ICommunicator
{
    Q_OBJECT

public:
    explicit TcpCommunicator(Parser *mParser);
    void setPort(int mPort);
    void setIP(QString mIp);
    void connectToHost();
    bool isConnected();
    int connectedState();
    QHostAddress getHostAddress();
    Parser *getParser();

signals:
    void newConnection();
    void lostConnection() ;
    void recieveMessage(QString);

public slots:
    void send(QString) ;
    void setConnection() ;
    void abortConnection() ;

protected slots:
    void read() ;

private:
    int         mPort;
    QString     mIp;
    QTcpSocket* mSocket;
    quint16     mBlockSize;
    Parser      *mParser;
    bool        hiMessage;
};

