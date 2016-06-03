#include <QDebug>
#include "gyroobserver.h"

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

