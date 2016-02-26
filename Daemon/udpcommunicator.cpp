#include "udpcommunicator.h"
#include <QTcpSocket>

UdpCommunicator::UdpCommunicator(QObject *parent) :
    QObject(parent),
    port(START_PORT_INT),
    blockSize(0)
{
}

void UdpCommunicator::listen()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug()<<"Unable to start the server: " << tcpServer->errorString();
        tcpServer->close();
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(setConnection()));
}

void UdpCommunicator::setPort(int numPort)
{
    port = numPort;
}

void UdpCommunicator::setConnection()
{
    QTcpSocket *bufferSocket = tcpServer->nextPendingConnection();
    hostIp = bufferSocket->peerAddress();
    bufferSocket->deleteLater();
    udpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    blockSize = 0;
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(udpSocket, SIGNAL(disconnected()), this, SLOT(abortConnection()));
    emit newConnection();
}

void UdpCommunicator::abortConnection()
{
    udpSocket->disconnectFromHost();
    emit lostConnection();
}

void UdpCommunicator::send(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    udpSocket->write(block);
}

void UdpCommunicator::read()
{
    QDataStream in(udpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    QString message;

    for (;;)
    {
        if (!blockSize)
        {
            if (udpSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> blockSize;
        }
        if (udpSocket->bytesAvailable() < blockSize)
        {
            break;
        }
        in >> message;
        blockSize = 0;
        emit recieveMessage(message);
    }
}
