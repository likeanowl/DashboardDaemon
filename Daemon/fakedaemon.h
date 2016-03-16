#pragma once

#include <telemetry_const.h>
#include <QObject>
#include <QVector>
#include <QTimer>
#include <fakeobserver.h>
#include <tcpcommunicator.h>
#include <udpcommunicator.h>
#include <icommunicator.h>
#include <QElapsedTimer>

class FakeObserver;
class FakeGyroObserver;
class FakeAccelObserver;
class FakeBatteryObserver;
class FakePowerMotorObserver;
class FakeEncoderObserver;

class FakeDaemon : public QObject
{
    Q_OBJECT
public:
    explicit FakeDaemon(QThread *guiThread, QString configPath);
    void attach(FakeObserver *fakeObs);

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
    TcpCommunicator* tcpCommunicator;
    UdpCommunicator* udpCommunicator;
    QVector<FakeObserver *> fakeObservers;
    FakeGyroObserver* fakeGyroObserver;
    FakeAccelObserver* fakeAccelObserver;
    FakeBatteryObserver* fakeBatteryObserver;
    FakePowerMotorObserver* fakePowerMotor1;
    FakePowerMotorObserver* fakePowerMotor2;
    FakePowerMotorObserver* fakePowerMotor3;
    FakePowerMotorObserver* fakePowerMotor4;
    FakeEncoderObserver* fakeEncoder1;
    FakeEncoderObserver* fakeEncoder2;
    FakeEncoderObserver* fakeEncoder3;
    FakeEncoderObserver* fakeEncoder4;

    QTimer timer;

    int pckgSize = 75;
    int count = 0;
    int updatePeriod;
};
