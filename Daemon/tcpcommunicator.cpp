#include "tcpcommunicator.h"

TcpCommunicator::TcpCommunicator() :
    port(START_PORT_INT),
    blockSize(0)
{
}

void TcpCommunicator::listen()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port))
    {
        qDebug()<<"Unable to start the server: " << tcpServer->errorString();
        tcpServer->close();
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(setConnection()));
}

QHostAddress TcpCommunicator::getHostAddress()
{
    return hostAddr;
}

void TcpCommunicator::setPort(int numPort)
{
    port = numPort;
}

void TcpCommunicator::setConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    tcpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    hostAddr = tcpSocket->peerAddress();
    blockSize = 0;
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
//    connect(tcpSocket, SIGNAL(disconnected()), tcpSocket, SLOT(deleteLater()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(abortConnection()));
    emit newConnection();
}

void TcpCommunicator::abortConnection()
{
    tcpSocket->disconnectFromHost();
    emit lostConnection();
}

void TcpCommunicator::send(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    qDebug() << new QString(block);
    tcpSocket->write(block);
}

void TcpCommunicator::read()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    QString message;

    for (;;)
    {
        if (!blockSize)
        {
            if (tcpSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> blockSize;
        }
        if (tcpSocket->bytesAvailable() < blockSize)
        {
            break;
        }
        in >> message;
        blockSize = 0;
        emit recieveMessage(message);
    }
}
