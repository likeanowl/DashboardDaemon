#pragma once

#include "observer.h"

/**
 * @brief AccelObserver class
 */
class AccelObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit AccelObserver(QString devName, trikControl::BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0 << 0.0 << 0.0;
    }
};
