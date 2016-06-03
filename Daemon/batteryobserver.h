#pragma once

#include "observer.h"

/**
 * @brief BatteryObserver class
 */
class BatteryObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit BatteryObserver(QString devName, trikControl::BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};
