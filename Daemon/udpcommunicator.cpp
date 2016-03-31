#include "udpcommunicator.h"

/**
 * @brief UdpCommunicator::UdpCommunicator
 */
UdpCommunicator::UdpCommunicator() :
    port(START_PORT_INT),
    blockSize(0)
{
}

/**
 * @brief Setting port
 * @param numPort
 */
void UdpCommunicator::setPort(int numPort)
{
    port = numPort;
}

/**
 * @brief Setting host address
 * @param hostAddress
 */
void UdpCommunicator::setHostAddr(QHostAddress hostAddress)
{
    hostAddr = hostAddress;
    this->setConnection();
}

/**
 * @brief Getting host address
 * @return
 */
QHostAddress UdpCommunicator::getHostAddr()
{
    return hostAddr;
}

/**
 * @brief Setting connection via UDP
 */
void UdpCommunicator::setConnection()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, port);
    blockSize = 0;
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(udpSocket, SIGNAL(disconnected()), this, SLOT(abortConnection()));
}

/**
 * @brief Aborting connection
 */
void UdpCommunicator::abortConnection()
{
    udpSocket->disconnectFromHost();
    emit lostConnection();
}

/**
 * @brief Sending message via UDP
 * @param message
 */
void UdpCommunicator::send(QString message)
{
    QByteArray block(message.toStdString().c_str());
    udpSocket->writeDatagram(block, hostAddr, port);
}

/**
 * @brief Reading incoming message
 */
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
