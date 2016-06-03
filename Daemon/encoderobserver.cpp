#include <QDebug>
#include "encoderobserver.h"

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
