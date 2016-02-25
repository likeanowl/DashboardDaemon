#pragma once
#include "telemetry_const.h"

#include <QObject>
#include <QVector>
#include <QTimer>
#include </home/likeanowl/trikRuntime/trikControl/include/trikControl/brickInterface.h>
#include "observer.h"
#include "tcpcommunicator.h"

using namespace trikControl;

class Observer;
class GyroObserver;
class AccelObserver;
class BatteryObserver;
class PowerMotorObserver;
class EncoderObserver;

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
    void parseMessage(QString message);

private:
    BrickInterface *brick;
    TcpCommunicator tcpCommunicator;
    QVector<Observer *> observers;
    GyroObserver *gyroObserver;
    AccelObserver *accelObserver;
    BatteryObserver* batteryObserver;
    PowerMotorObserver* powerMotor1;
    PowerMotorObserver* powerMotor2;
    PowerMotorObserver* powerMotor3;
    PowerMotorObserver* powerMotor4;
    EncoderObserver* encoder1;
    EncoderObserver* encoder2;
    EncoderObserver* encoder3;
    EncoderObserver* encoder4;

    QTimer timer;

    int updatePeriod;
};
