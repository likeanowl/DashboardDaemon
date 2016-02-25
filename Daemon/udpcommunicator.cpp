#include "udpcommunicator.h"

UdpCommunicator::UdpCommunicator(QObject *parent) :
    QObject(parent),
    port(START_PORT_INT),
    blockSize(0)
{
}

void UdpCommunicator::listen()
{
    tcpServer = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, port)) {
        qDebug()<<"Unable to start the server: " << server->errorString();
        server->close();
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(setConnection()));
}

void UdpCommunicator::setPort(int numPort)
{
    port = numPort;
}

void UdpCommunicator::setConnection()
{
    socket = server->nextPendingConnection();
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    blockSize = 0;
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
//    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(abortConnection()));
    emit newConnection();
}

void UdpCommunicator::abortConnection()
{
    socket->disconnectFromHost();
    emit lostConnection();
}

void UdpCommunicator::send(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    udpSocket->write(block);
}

void UdpCommunicator::read()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);
    QString message;

    for (;;)
    {
        if (!blockSize)
        {
            if (socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> blockSize;
        }
        if (socket->bytesAvailable() < blockSize)
        {
            break;
        }
        in >> message;
        blockSize = 0;
        emit recieveMessage(message);
    }
}
