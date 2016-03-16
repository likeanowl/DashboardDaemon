#pragma once

#include "telemetry_const.h"
#include "toolbar.h"
#include "isensorwidget.h"

#include <QMainWindow>
#include <QDockWidget>
#include <QTranslator>
#include <QPair>
#include <QMap>

class IDataSource;
class ControlPanel : public QMainWindow
{
    Q_OBJECT
public:
    ControlPanel(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    QTranslator appTranslator;

    void changeEvent(QEvent *event);

signals:
    void newConnection();
    void lostConnection();
    void setConnection(QString ip, int port);
    void requestDataToSubscribe(QString, QString);
    void requestDataToUnscribe(QString, QString);

public slots:
    void setStatusBarText(const QString text);
    void subscribeWidgetToDataSource(IDataSource *dataSource, QString widgetName, QString deviceName);
    void unscribeWidgetFromDataSource(IDataSource *dataSource, QString widgetName, QString deviceName);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void retranslateUi();
    void createSensorWidget(QString widgetName, QString sensorName);
    void createDockWidget(QDockWidget *dw);
    void deleteSensorWidget(QString widgetName, QString sensorName);

private:
    ToolBar *mToolBar;
    QMap<QString, QPair<QDockWidget *, ISensorWidget * > > mWidgets;
};
