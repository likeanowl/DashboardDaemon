#pragma once

#include <QObject>
#include <QVector>
#include <QTimer>
#include "brickInterface.h"
#include "accelobserver.h"
#include "batteryobserver.h"
#include "encoderobserver.h"
#include "powermotorobserver.h"
#include "gyroobserver.h"
#include "tcpcommunicator.h"
#include "udpcommunicator.h"
#include "telemetry_const.h"

class Daemon : public QObject
{
    Q_OBJECT
public:
    explicit Daemon(QThread *guiThread, QString configPath);
    void attach(Observer *obs);

signals:

public slots:

private slots:
    void testSensors(int times);
    void notify();
    void zipPackage();
    void startTelemetry();
    void closeTelemetry();
    const void parseMessage(QString message) const;

private:
    trikControl::BrickInterface *brick = nullptr;
    TcpCommunicator *tcpCommunicator   = nullptr;
    UdpCommunicator *udpCommunicator   = nullptr;

    QVector<Observer*> observers       = QVector<Observer*>();

    GyroObserver *gyroObserver         = nullptr;

    AccelObserver *accelObserver       = nullptr;

    BatteryObserver* batteryObserver   = nullptr;

    PowerMotorObserver* powerMotor1    = nullptr;
    PowerMotorObserver* powerMotor2    = nullptr;
    PowerMotorObserver* powerMotor3    = nullptr;
    PowerMotorObserver* powerMotor4    = nullptr;

    EncoderObserver* encoder1          = nullptr;
    EncoderObserver* encoder2          = nullptr;
    EncoderObserver* encoder3          = nullptr;
    EncoderObserver* encoder4          = nullptr;

    QTimer timer;

    int updatePeriod;
};
