#pragma once
#include "telemetry_const.h"
#include "parser.h"
#include <QHostAddress>
#include <QObject>

class ICommunicator : public QObject
{
    Q_OBJECT

public:
    virtual void setPort(int port) = 0;
    virtual void setIP(QString ip) = 0;
    virtual void connectToHost() = 0;
    virtual bool isConnected() = 0;
    virtual int connectedState() = 0;
    virtual Parser *getParser() = 0;
    virtual QHostAddress getHostAddress() = 0;

signals:
    void newConnection();
    void lostConnection();
    void recieveMessage(QString);

public slots:
    virtual void send(QString) = 0;
    virtual void setConnection() = 0;
    virtual void abortConnection() = 0;

protected slots:
    virtual void read() = 0;
};
