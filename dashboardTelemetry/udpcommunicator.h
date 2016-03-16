#pragma once

#include "icommunicator.h"
#include "parser.h"
#include <QUdpSocket>
#include <QDataStream>

class UdpCommunicator : public ICommunicator
{
    Q_OBJECT

public:
    explicit UdpCommunicator(Parser *mParser);
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
    void readyRead();

public slots:
    void send(QString) ;
    void setConnection() ;
    void abortConnection() ;

protected slots:
    void read() ;

private:
    int             mPort;
    QHostAddress    mIp;
    QUdpSocket*     mSocket;
    quint16         mBlockSize;
    Parser          *mParser;
    bool            hiMessage;
};

