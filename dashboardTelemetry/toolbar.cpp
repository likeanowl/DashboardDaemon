#include "toolbar.h"

#include <QMainWindow>
#include <QMenu>
#include <QComboBox>
#include <QBoxLayout>
#include <QGroupBox>
#include <stdlib.h>

ToolBar::ToolBar()
    : QToolBar()
{
    menuBox = new QToolBox();
    setMovable(false);
    this->setFixedWidth(TOOLBAR_WIDTH);

    insertToolBox();

    retranslateUi();
}

void ToolBar::retranslateUi()
{
    mIpLabel->setText(tr("Connect to IP:"));
    mPortLabel->setText(tr("Port:"));
    mConnectButton->setText(tr("Connect"));
    menuBox->setItemText(0, tr("Connection"));
    menuBox->setItemText(1, tr("Settings"));
    if (menuBox->count() > 2) {
        menuBox->setItemText(2, tr("Telemetry"));
        mTelemetry->setItemText(0, tr("3D sensors"));
        mTelemetry->setItemText(1, tr("Analog sensors"));
        mTelemetry->setItemText(2, tr("Servomotors"));
        mTelemetry->setItemText(3, tr("Motors"));
        mTelemetry->setItemText(4, tr("Encoders"));
        mTelemetry->setItemText(5, tr("Battery"));
        mTelemetry->setItemText(6, tr("Camera"));
    }
}

void ToolBar::insertToolBox()
{
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border-radius: 3px; color: darkgray; }"
                       "QToolBox::tab:selected { font: italic; color: black;}");

    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    mIpLabel = new QLabel();
    mIpTextEdit = new QLineEdit(START_IP_STRING);
    mPortLabel = new QLabel();
    mPortTextEdit = new QLineEdit(START_PORT_STRING);
    mConnectButton = new QPushButton();
    mConnectButton->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                                 "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    mIpTextEdit->setFixedHeight(IPTEXT_HEIGHT);
    mPortTextEdit->setFixedHeight(PORTTEXT_HEIGHT);
    connectToTRIKLayout->addWidget(mIpLabel);
    connectToTRIKLayout->addWidget(mIpTextEdit);
    connectToTRIKLayout->addWidget(mPortLabel);
    connectToTRIKLayout->addWidget(mPortTextEdit);
    connectToTRIKLayout->addWidget(mConnectButton);
    connectToTRIKLayout->addStretch(0);
    connectToTRIK->setLayout(connectToTRIKLayout);
    menuBox->addItem(connectToTRIK, "");

    connect(mConnectButton, &QPushButton::clicked, this, &ToolBar::connectButtonPressed);

    QGroupBox *settings = new QGroupBox();
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    QComboBox *box = new QComboBox();
    box->clear();

    settingsLayout->addWidget(box);
    settingsLayout->addStretch(0);
    settings->setLayout(settingsLayout);
    menuBox->addItem(settings, "");

    this->addWidget(menuBox);
}

void ToolBar::insertTelemetry()
{
    mTelemetry = new QToolBox();
    mTelemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(mTelemetry, "");

    QVector<QString> nameOfWidgets;

    //3D sensors
    nameOfWidgets.append(TelemetryConst::ACCELEROMETER_TITLE());
    nameOfWidgets.append(TelemetryConst::GYROSCOPE_TITLE());
    insertGroupOfWidgets(nameOfWidgets);

    //analog sensors
    insertGroupOfWidgets(nameOfWidgets);

    //servomotors
    insertGroupOfWidgets(nameOfWidgets);

    //power motors
    nameOfWidgets.append(TelemetryConst::POWER_MOTOR1_TITLE());
    nameOfWidgets.append(TelemetryConst::POWER_MOTOR2_TITLE());
    nameOfWidgets.append(TelemetryConst::POWER_MOTOR3_TITLE());
    nameOfWidgets.append(TelemetryConst::POWER_MOTOR4_TITLE());
    insertGroupOfWidgets(nameOfWidgets);

    //encoders
    insertGroupOfWidgets(nameOfWidgets);

    //batteryGroup
    nameOfWidgets.append(TelemetryConst::BATTERY_TITLE());
    insertGroupOfWidgets(nameOfWidgets);

    //camera
    insertGroupOfWidgets(nameOfWidgets);

    connectButtons();
    retranslateUi();
}

void ToolBar::insertGroupOfWidgets(QVector<QString> &nameOfWidgets)
{
    QGroupBox *groupBox = new QGroupBox();
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    QToolBox *groupToolBox = new QToolBox();

    for (int i = 0; i != nameOfWidgets.count(); ++i) {
        QGroupBox *widgetGroupBox = new QGroupBox();
        QVBoxLayout *widgetLayout = new QVBoxLayout;
        if (nameOfWidgets.at(i) == TelemetryConst::ACCELEROMETER_TITLE() ||
            nameOfWidgets.at(i) == TelemetryConst::GYROSCOPE_TITLE()) {
            widgetLayout->addWidget(createPlotButton(nameOfWidgets.at(i)));
        } else if (nameOfWidgets.at(i) == TelemetryConst::BATTERY_TITLE()) {
            widgetLayout->addWidget(createLCDNumberButton(nameOfWidgets.at(i)));
        } else if (nameOfWidgets.at(i) == TelemetryConst::POWER_MOTOR1_TITLE() ||
                   nameOfWidgets.at(i) == TelemetryConst::POWER_MOTOR2_TITLE() ||
                   nameOfWidgets.at(i) == TelemetryConst::POWER_MOTOR3_TITLE() ||
                   nameOfWidgets.at(i) == TelemetryConst::POWER_MOTOR4_TITLE()) {
            widgetLayout->addWidget(createProgressBarButton(nameOfWidgets.at(i)));
        }

        widgetLayout->addWidget(createTableButton(nameOfWidgets.at(i)));
        widgetGroupBox->setLayout(widgetLayout);
        groupToolBox->addItem(widgetGroupBox, "");
        groupToolBox->setItemText(i, nameOfWidgets.at(i));
        vBoxLayout->addWidget(groupToolBox);
    }
    vBoxLayout->addStretch(0);
    groupBox->setLayout(vBoxLayout);
    mTelemetry->addItem(groupBox, "");
    nameOfWidgets.clear();
}

WidgetButton *ToolBar::createPlotButton(QString deviceName)
{
    WidgetButton *plotButton = new WidgetButton(TelemetryConst::PLOT_TITLE(), deviceName);
    mWidgetButtons.append(plotButton);
    return plotButton;
}

WidgetButton *ToolBar::createLCDNumberButton(QString deviceName)
{
    WidgetButton *lcdNumberButton = new WidgetButton(TelemetryConst::LCDNUMBER_TITLE(), deviceName);
    mWidgetButtons.append(lcdNumberButton);
    return lcdNumberButton;
}

WidgetButton *ToolBar::createProgressBarButton(QString deviceName)
{
    WidgetButton *progressBarButton = new WidgetButton(TelemetryConst::PROGRESSBAR_TITLE(), deviceName);
    mWidgetButtons.append(progressBarButton);
    return progressBarButton;
}

WidgetButton *ToolBar::createTableButton(QString deviceName)
{
    WidgetButton *tableButton = new WidgetButton(TelemetryConst::TABLE_TITLE(), deviceName);
    mWidgetButtons.append(tableButton);
    return tableButton;
}

void ToolBar::connectButtons()
{
    for (int i = 0; i != mWidgetButtons.count(); ++i) {
        connect(mWidgetButtons.at(i), &WidgetButton::sendDataFromButton,
                this, &ToolBar::widgetButtonIsPressed);
    }
}

void ToolBar::deleteTelemetry()
{
    menuBox->deleteLater();

    int numOfWidgets = mWidgetButtons.count();
    for (int i = 0; i != numOfWidgets; ++i) {
        delete mWidgetButtons.at(i);
    }

    mWidgetButtons.clear();

    menuBox = new QToolBox();
    insertToolBox();
}

void ToolBar::enterEvent(QEvent*)
{
}

void ToolBar::leaveEvent(QEvent*)
{
}

void ToolBar::connectButtonPressed()
{
    int port = mPortTextEdit->text().trimmed().toInt();
    emit setConnection(mIpTextEdit->text(), port);
}

void ToolBar::widgetButtonIsPressed(QString widgetName, QString deviceName, bool isActive)
{
    if (isActive) {
        emit requestDataToSubscribe(widgetName, deviceName);
    } else {
        emit requestDataToUnscribe(widgetName, deviceName);
    }
}
