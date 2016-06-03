#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "telemetry_const.h"
#include "brickInterface.h"

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
    explicit Observer(QString devName, trikControl::BrickInterface* brick, Daemon* daemon);

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
    QTimer* timer = nullptr;
    QString name;
    int updateInterval;
    QVector<float> value;
    bool canRead;
    bool newData;
    trikControl::BrickInterface *brickbase = nullptr;
};
