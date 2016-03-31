#include <QDebug>
#include "observer.h"

/**
 * @brief Observer::Observer
 * @param devName
 * @param brick
 * @param daemon
 */
Observer::Observer(QString devName, BrickInterface *brick, Daemon* daemon)
{
    name = devName;
    newData = false;
    updateInterval = 1000;
    canRead = false;
    timer = new QTimer(this);
    brickbase = brick;
    daemon->attach(this);
}

/**
 * @brief GyroObserver::update
 */
void GyroObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = brickbase->gyroscope()->read();
    QVector<float> out;
    int n = temp.size();
    for (int i = 0; i < n; i++)
    {
        int x = temp.at(i);
        out << (float)x;
    }
    value = out;
}

/**
 * @brief AccelObserver::update
 */
void AccelObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = brickbase->accelerometer()->read();
    QVector<float> out;
    int n = temp.size();
    for (int i = 0; i < n; i++)
    {
        int x = temp.at(i);
        out << (float)x;
    }
    value = out;
}

/**
 * @brief BatteryObserver::update
 */
void BatteryObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << brickbase->battery()->readVoltage();
    value = temp;
}

/**
 * @brief PowerMotorObserver::update
 */
void PowerMotorObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << brickbase->motor(name)->power();
    value = temp;
}

/**
 * @brief EncoderObserver::update
 */
void EncoderObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << brickbase->encoder(name)->read();
    value = temp;
}
