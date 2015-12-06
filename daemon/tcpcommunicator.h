#pragma once
#include "telemetry_const.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit TcpCommunicator(QObject *parent = 0);
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
    QTcpServer* server;
    QTcpSocket* socket;
    quint16     blockSize;
};
