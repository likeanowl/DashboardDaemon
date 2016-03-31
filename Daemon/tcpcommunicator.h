#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include "icommunicator.h"
#include "telemetry_const.h"

class TcpCommunicator : public ICommunicator
{
    Q_OBJECT
public:
    explicit TcpCommunicator();
    void setPort(int port);
    void listen();
    QHostAddress getHostAddress();

signals:
    void newConnection();
    void lostConnection();
    void recieveMessage(QString);

public slots:
    void send(QString);

private slots:
    void setConnection();
    void abortConnection();
    void read();

private:
    QHostAddress hostAddr;
    int         port;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    quint16     blockSize;
};
