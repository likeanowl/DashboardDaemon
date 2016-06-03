#include <QDebug>
#include "powermotorobserver.h"

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
