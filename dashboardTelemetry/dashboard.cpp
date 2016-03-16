#include "dashboard.h"
#include <QThread>

Dashboard::Dashboard(ICommunicator *tcpCommunicator, ICommunicator *udpCommunicator)
{
    connect(&mPanel, &ControlPanel::setConnection, this, &Dashboard::connectToTRIK);

    mFacade = new Facade(tcpCommunicator, udpCommunicator);

    mPanel.resize(PANEL_START_SIZE);
    mPanel.setMinimumSize(PANEL_MIN_SIZE);
    mPanel.show();

    connect(&mPanel, &ControlPanel::requestDataToSubscribe, mFacade, &Facade::requestDataToSubscribe);
    connect(&mPanel, &ControlPanel::requestDataToUnscribe, mFacade, &Facade::requestDataToUnscribe);

    connect(mFacade, &Facade::subscribeWidgetToDataSource, &mPanel, &ControlPanel::subscribeWidgetToDataSource);
    connect(mFacade, &Facade::unscribeWidgetFromDataSource, &mPanel, &ControlPanel::unscribeWidgetFromDataSource);

}

void Dashboard::connectToTRIK(QString ip, int port)
{
    mPanel.setStatusBarText(TelemetryConst::WAITING_RESPONSE_MESSAGE());
    QThread::msleep(WAITING_RESPONSE_TIME);
    if (mFacade->connectToTRIK(ip, port)) {
        mPanel.setStatusBarText(TelemetryConst::SEND_FROM_DAEMON_MESSAGE());
        emit mPanel.newConnection();
    } else {
        mPanel.setStatusBarText(TelemetryConst::NOCONNECTION_MESSAGE());
    }
}
