#pragma once

#include "observer.h"

/**
 * @brief EncoderObserver class
 */
class EncoderObserver: public Observer
{
    Q_OBJECT

public slots:
    void update();

public:
    explicit EncoderObserver(QString devName, trikControl::BrickInterface *brick, Daemon* daemon):
        Observer(devName, brick, daemon)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        value << 0.0;
    }
};
