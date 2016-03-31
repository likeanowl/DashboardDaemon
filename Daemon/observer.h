#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "telemetry_const.h"
#include "brickInterface.h"
#include "daemon.h"

using namespace trikControl;

class Daemon;
/**
 * @brief Observer class - declares observers for controller sensors
 */
class Observer : public QObject
{
    Q_OBJECT

public slots:
    virtual void update() = 0;

public:
    /**
     * @brief Constructor
     * @param devName
     * @param brick
     * @param daemon
     */
    explicit Observer(QString devName, BrickInterface *brick, Daemon* daemon);

    /**
     * @brief Returning sensor data
     * @return value
     */
    QVector<float> getValue()
    {
        newData = false;
        return value;
    }

    /**
     * @brief Subscribes an observer to sensor data updates
     */
    void subscribe() {
        timer->start(updateInterval);
        canRead = true;
    }

    /**
     * @brief Unsubsribes an observer from data updates
     */
    void unsubscribe() {
        timer->stop();
        canRead = false;
    }

    /**
     * @brief Returning name of sensor
     * @return name
     */
    QString getName() { return name; }
    /**
     * @brief Setting update interval
     * @param interval
     */
    void setUpdateInterval(int interval) { updateInterval = interval; }
    /**
     * @brief Returns if an observer subsribed to sensor
     * @return canRead
     */
    bool subscribed() { return canRead; }
    /**
     * @brief Returns if sensor's data is updated
     * @return newData
     */
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

/**
 * @brief AccelObserver class
 */
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

/**
 * @brief BatteryObserver class
 */
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

/**
 * @brief PowerMotorObserver class
 */
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

/**
 * @brief EncoderObserver class
 */
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
