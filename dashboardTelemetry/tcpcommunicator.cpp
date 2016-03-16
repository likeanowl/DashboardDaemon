#include "tcpcommunicator.h"

TcpCommunicator::TcpCommunicator(Parser *parser) :
    mPort(START_PORT_INT),
    mIp(START_IP_STRING),
    mBlockSize(0),
    mParser(parser),
    hiMessage(true)
{
    mSocket = new QTcpSocket(this);
    connect(mSocket, &QTcpSocket::readyRead, this, &TcpCommunicator::read);
    connect(mSocket, &QTcpSocket::connected, this, &TcpCommunicator::setConnection);
    connect(mSocket, &QTcpSocket::disconnected, this, &TcpCommunicator::abortConnection);
    connect(this, &TcpCommunicator::recieveMessage, this->mParser, &Parser::parseMessage);
}

QHostAddress TcpCommunicator::getHostAddress()
{
    return mSocket->peerAddress();
}

void TcpCommunicator::setConnection()
{
    emit newConnection();
}

void TcpCommunicator::abortConnection()
{
    emit lostConnection();
}

void TcpCommunicator::setIP(QString ipString)
{
    mIp = ipString;
}

void TcpCommunicator::setPort(int numPort)
{
    mPort = numPort;
}

int TcpCommunicator::connectedState()
{
    return mSocket->ConnectedState;
}

void TcpCommunicator::connectToHost()
{
    mBlockSize = 0;
    mSocket->abort();
    mSocket->connectToHost(mIp, mPort);
}

bool TcpCommunicator::isConnected()
{
    return (connectedState() == QTcpSocket::ConnectedState);
}

Parser *TcpCommunicator::getParser()
{
    return mParser;
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
    mSocket->write(block);
}

void TcpCommunicator::read()
{
    if (hiMessage)
    {
        hiMessage = false;
        return;
    }

    QDataStream in(mSocket);
    in.setVersion(QDataStream::Qt_4_0);
    QString message;

    for (;;)
    {
        if (!mBlockSize)
        {
            if (mSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> mBlockSize;
        }
        if (mSocket->bytesAvailable() < mBlockSize)
        {
            break;
        }
        in >> message;
        mBlockSize = 0;
        emit recieveMessage(message);
    }
}
