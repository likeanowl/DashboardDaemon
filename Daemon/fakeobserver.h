#pragma once

#include <QObject>
#include <QTimer>
#include <random>
#include "telemetry_const.h"
#include "fakedaemon.h"

class FakeDaemon;

class FakeObserver : public QObject
{
    Q_OBJECT

public slots:
    virtual void update() = 0;

public:
    explicit FakeObserver(QString devName, FakeDaemon* fakeDaemon);

    QVector<float> getValue()
    {
        newData = false;
        return value;
    }
    void subscribe() {
        timer->start(updateInterval);
        canRead = true;
    }
    void unsubscribe() {
        timer->stop();
        canRead = false;
    }

    QString getName() { return name; }
    void setUpdateInterval(int interval) { updateInterval = interval; }
    bool subscribed() { return canRead; }
    bool freshData() { return newData; }

protected:
    QTimer* timer;
    QString name;
    int updateInterval;
    QVector<float> value;
    bool canRead;
    bool newData;
};

class FakeGyroObserver: public FakeObserver
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit FakeGyroObserver(QString devName, FakeDaemon* fakeDaemon):
        FakeObserver(devName, fakeDaemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0 << 0.0 << 0.0;
    }
};

class FakeAccelObserver: public FakeObserver
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit FakeAccelObserver(QString devName, FakeDaemon* fakeDaemon):
        FakeObserver(devName, fakeDaemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0 << 0.0 << 0.0;
    }
};

class FakeBatteryObserver: public FakeObserver
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit FakeBatteryObserver(QString devName, FakeDaemon* fakeDaemon):
        FakeObserver(devName, fakeDaemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};

class FakePowerMotorObserver: public FakeObserver
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit FakePowerMotorObserver(QString devName, FakeDaemon* fakeDaemon):
        FakeObserver(devName, fakeDaemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};

class FakeEncoderObserver: public FakeObserver
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit FakeEncoderObserver(QString devName, FakeDaemon* fakeDaemon):
        FakeObserver(devName, fakeDaemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};
