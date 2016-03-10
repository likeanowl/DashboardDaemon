#pragma once
#include "telemetry_const.h"
#include <QTcpServer>
#include <QUdpSocket>
#include <QDataStream>
#include <icommunicator.h>

class UdpCommunicator : public ICommunicator
{
    Q_OBJECT
public:
    explicit UdpCommunicator();
    void setPort(int port);
    void listen();

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
    int         port;
    QTcpServer* tcpServer;
    QUdpSocket* udpSocket;
    QHostAddress hostAddr;
    quint16     blockSize;
};
