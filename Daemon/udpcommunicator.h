#pragma once
#include "telemetry_const.h"
#include <QObject>
#include <QTcpServer>
#include <QUdpSocket>
#include <QDataStream>

class UdpCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit UdpCommunicator(QObject *parent = 0);
    void setPort(int port);
    void listen();

signals:
    void newConnection();
    void lostConnection();
    void recieveMessage(QString);

public slots:
    void send(QString);

private slots:
    void bindSocket();
    void abortConnection();
    void readNextDatagram();

private:
    int         port;
    QTcpServer* tcpServer;
    QUdpSocket* udpSocket;
    QHostAddress hostAddr;
    quint16     blockSize;
};
