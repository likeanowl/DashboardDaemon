#include <QDebug>
#include "fakeobserver.h"

/**
 * @brief FakeObserver::FakeObserver
 * @param devName
 * @param fakeDaemon
 */
FakeObserver::FakeObserver(QString devName, FakeDaemon* fakeDaemon)
{
    name = devName;
    newData = false;
    updateInterval = 1000;
    canRead = false;
    timer = new QTimer(this);
    fakeDaemon->attach(this);
}

/**
 * @brief FakeGyroObserver::update
 */
void FakeGyroObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = {rand() % 20 + 10, rand() % 20 + 10, rand() % 20 + 10};
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
 * @brief FakeAccelObserver::update
 */
void FakeAccelObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = {rand() % 10 + 10, rand() % 10 + 10, rand() % 10 + 10};
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
 * @brief FakeBatteryObserver::update
 */
void FakeBatteryObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << rand() % 10 + 10;
    value = temp;
}

/**
 * @brief FakePowerMotorObserver::update
 */
void FakePowerMotorObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << rand() % 10 + 10;
    value = temp;
}

/**
 * @brief FakeEncoderObserver::update
 */
void FakeEncoderObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << rand() % 10 + 10;
    value = temp;
}
