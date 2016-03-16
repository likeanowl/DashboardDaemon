#include "facade.h"

Facade::Facade(ICommunicator *tcpCommunicator, ICommunicator *udpCommunicator) :
    mTCommunicator(tcpCommunicator),
    mUCommunicator(udpCommunicator)
{
    mParser = tcpCommunicator->getParser();
    connect(mParser, &Parser::subscribeWidgetToDataSource, this, &Facade::subscribeWidgetToDataSource);
}

bool Facade::connectToTRIK(QString ip, int port)
{
    mTCommunicator->setIP(ip.toLatin1());
    mUCommunicator->setIP(ip.toLatin1());
    mTCommunicator->setPort(port);
    mUCommunicator->setPort(1222);
    mTCommunicator->connectToHost();
    mUCommunicator->connectToHost();
    mTCommunicator->send(SEND_MESSAGE);

    return mTCommunicator->isConnected() && mUCommunicator->isConnected();
}

void Facade::requestDataToSubscribe(QString widgetName, QString deviceName)
{
    mParser->requestDataToSubscribe(widgetName, deviceName);
}

void Facade::requestDataToUnscribe(QString widgetName, QString deviceName)
{
    mParser->requestDataToUnscribe(widgetName, deviceName);
}
