#include "udpcommunicator.h"
#include <QTcpSocket>

UdpCommunicator::UdpCommunicator() :
    port(START_PORT_INT),
    blockSize(0)
{
}

void UdpCommunicator::setPort(int numPort)
{
    port = numPort;
}

void UdpCommunicator::setHostAddr(QHostAddress hostAddress)
{
    hostAddr = hostAddress;
    this->setConnection();
}

void UdpCommunicator::setConnection()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(hostAddr, port);
    qDebug() << "Socked binded to " << hostAddr.toString() << " " << port;
    blockSize = 0;
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(udpSocket, SIGNAL(disconnected()), this, SLOT(abortConnection()));
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
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    udpSocket->writeDatagram(block, hostAddr, port);
}

void UdpCommunicator::read()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString message(datagram.data());
        qDebug() << message;
        emit recieveMessage(message);
    }
    /*QDataStream in(udpSocket);
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
    }*/
}
