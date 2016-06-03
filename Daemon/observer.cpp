#include <QDebug>
#include "observer.h"
#include "daemon.h"

Observer::Observer(QString devName, trikControl::BrickInterface *brick, Daemon* daemon)
{
    name = devName;
    newData = false;
    updateInterval = 1000;
    canRead = false;
    timer = new QTimer(this);
    brickbase = brick;
    daemon->attach(this);
}
