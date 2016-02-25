#include "fakeobserver.h"
#include <QDebug>

FakeObserver::FakeObserver(QString devName, FakeDaemon* fakeDaemon)
{
    name = devName;
    newData = false;
    updateInterval = 1000;
    canRead = false;
    timer = new QTimer(this);
    fakeDaemon->attach(this);
}

void FakeGyroObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = {10, 10, 10};
    QVector<float> out;
    int n = temp.size();
    for (int i = 0; i < n; i++)
    {
        int x = temp.at(i);
        out << (float)x;
    }
    value = out;
}

void FakeAccelObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<int> temp = {10, 10, 10};
    QVector<float> out;
    int n = temp.size();
    for (int i = 0; i < n; i++)
    {
        int x = temp.at(i);
        out << (float)x;
    }
    value = out;
}

void FakeBatteryObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << 14;
    value = temp;
}

void FakePowerMotorObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << 15;
    value = temp;
}

void FakeEncoderObserver::update()
{
    newData = true;
    if (!canRead)
    {
        return;
    }
    QVector<float> temp;
    temp << 16;
    value = temp;
}
