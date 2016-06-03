#pragma once

#include "observer.h"

class GyroObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit GyroObserver(QString devName, trikControl::BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0 << 0.0 << 0.0;
    }
};
