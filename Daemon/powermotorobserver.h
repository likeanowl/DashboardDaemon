#pragma once

#include "observer.h"

/**
 * @brief PowerMotorObserver class
 */
class PowerMotorObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit PowerMotorObserver(QString devName, trikControl::BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};
