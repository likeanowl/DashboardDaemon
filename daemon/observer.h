#pragma once
#include "telemetry_const.h"

#include </trikRuntime/trikControl/include/trikControl/brickInterface.h>
#include "daemon.h"
#include <QObject>
#include <QTimer>

using namespace trikControl;

class Daemon;

class Observer : public QObject
{
    Q_OBJECT

public slots:
    virtual void update() = 0;

public:
    explicit Observer(QString devName, BrickInterface *brick, Daemon* daemon);

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
    BrickInterface *brickbase;
};

class GyroObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit GyroObserver(QString devName, BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0 << 0.0 << 0.0;
    }
};

class AccelObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit AccelObserver(QString devName, BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0 << 0.0 << 0.0;
    }
};

class BatteryObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit BatteryObserver(QString devName, BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};

class PowerMotorObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit PowerMotorObserver(QString devName, BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};

class EncoderObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit EncoderObserver(QString devName, BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};
