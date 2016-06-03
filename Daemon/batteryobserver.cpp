#include <QDebug>
#include "batteryobserver.h"

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
