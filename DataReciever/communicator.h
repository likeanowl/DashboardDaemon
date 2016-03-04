#pragma once
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Communicator : public QObject
{
    Q_OBJECT

public:
    explicit Communicator();
    void connectToHost();
    bool isConnected();
    int connectedState();

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
    int         mPort = 1221;
    QString     mIp = "127.0.0.1";
    QTcpSocket* mSocket;
    quint16     mBlockSize;
    bool        hiMessage;
};

