#pragma once
#include "telemetry_const.h"
#include <QObject>

class ICommunicator : public QObject
{
    Q_OBJECT

public:
    virtual void setPort(int port) = 0;
    virtual void listen() = 0;
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
