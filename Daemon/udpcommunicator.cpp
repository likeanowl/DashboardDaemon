#include "udpcommunicator.h"

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

QHostAddress UdpCommunicator::getHostAddr()
{
    return hostAddr;
}

void UdpCommunicator::setConnection()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, port);
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
    QByteArray block(message.toStdString().c_str());
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
}
