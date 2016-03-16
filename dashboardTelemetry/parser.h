#pragma once

#include <QObject>
#include <QMap>
#include <QVector>
#include "idatasource.h"
#include "telemetry_const.h"

class Parser : public QObject
{
    Q_OBJECT

public:
    Parser();

public slots:
    void parseMessage(QString message);
    void sendData(QString deviceName, QVector<float> values);
    void requestDataToSubscribe(QString widgetName, QString deviceName);
    void requestDataToUnscribe(QString widgetName, QString deviceName);

signals:
    void messageIsParsed(QString, QVector<float>);
    void subscribeWidgetToDataSource(IDataSource *, QString, QString);
    void unscribeWidgetFromDataSource(IDataSource *, QString, QString);

private slots:
    void addDataSource(QString deviceName, IDataSource *newDataSource);

private:
    QMap<QString, IDataSource *> mMap;
};

