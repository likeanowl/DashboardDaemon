#pragma once

#include <QPushButton>
#include <QObject>

class WidgetButton : public QPushButton
{
    Q_OBJECT
public:
    WidgetButton(QString text, QString mSensorName);
    QString getSensorName();
    bool isActive();

signals:
    void sendDataFromButton(QString, QString, bool);

private slots:
    void buttonIsClicked();

private:
    QString mSensorName;
    bool mWidgetIsActive;
};
