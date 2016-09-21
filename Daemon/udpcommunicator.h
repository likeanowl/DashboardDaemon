#pragma once

#include <QUdpSocket>
#include <QDataStream>
#include "icommunicator.h"
#include "telemetry_const.h"

class UdpCommunicator : public ICommunicator
{
    Q_OBJECT
public:
    explicit UdpCommunicator();
    void setPort(int port);
    void setHostAddr(QHostAddress hostAddress);
    QHostAddress getHostAddr();

signals:
    void newConnection();
    void lostConnection();
    void recieveMessage(QString);

public slots:
    void send(const QString &);

private slots:
    void setConnection();
    void abortConnection();
    void read();

private:
    int         port;
    QUdpSocket* udpSocket = nullptr;
    QHostAddress hostAddr;
    quint16     blockSize;
};
