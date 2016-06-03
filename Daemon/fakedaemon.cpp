#include <QDebug>
#include <QStringList>
#include "fakedaemon.h"

/**
 * @brief Constructor
 * @param guiThread
 * @param configPath
 */
FakeDaemon::FakeDaemon(QThread *guiThread, QString configPath)
{
    updatePeriod = TCP_PEDIOD;
    tcpCommunicator = new TcpCommunicator();
    udpCommunicator = new UdpCommunicator();
    tcpCommunicator->setPort(START_PORT_INT);
    tcpCommunicator->listen();
    udpCommunicator->setPort(START_PORT_INT);
    connect(tcpCommunicator, SIGNAL(newConnection()), this, SLOT(startTelemetry()));
    connect(tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    connect(tcpCommunicator, SIGNAL(lostConnection()), this, SLOT(closeTelemetry()));

    fakeGyroObserver = new FakeGyroObserver(GYROSCOPE_NAME, this);
    fakeGyroObserver->setUpdateInterval(SENSORS3D_DATA_UPDATE_PERIOD);
    fakeAccelObserver = new FakeAccelObserver(ACCELEROMETER_NAME, this);
    fakeAccelObserver->setUpdateInterval(SENSORS3D_DATA_UPDATE_PERIOD);
    fakeBatteryObserver = new FakeBatteryObserver(BATTERY_NAME, this);
    fakeBatteryObserver->setUpdateInterval(BATTERY_DATA_UPDATE_PERIOD);

    fakePowerMotor1 = new FakePowerMotorObserver(POWER_MOTOR1_NAME, this);
    fakePowerMotor1->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);
    fakePowerMotor2 = new FakePowerMotorObserver(POWER_MOTOR2_NAME, this);
    fakePowerMotor2->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);
    fakePowerMotor3 = new FakePowerMotorObserver(POWER_MOTOR3_NAME, this);
    fakePowerMotor3->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);
    fakePowerMotor4 = new FakePowerMotorObserver(POWER_MOTOR4_NAME, this);
    fakePowerMotor4->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);

    fakeEncoder2 = new FakeEncoderObserver(ENCODER2_NAME, this);
    fakeEncoder2->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);
    fakeEncoder3 = new FakeEncoderObserver(ENCODER3_NAME, this);
    fakeEncoder3->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);
    fakeEncoder4 = new FakeEncoderObserver(ENCODER4_NAME, this);
    fakeEncoder4->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);

    for (int i = 0; i < fakeObservers.size(); i++)
        qDebug() << fakeObservers[i]->getName();

    testSensors(2);
}

/**
 * @brief FakeDaemon::testSensors
 * @param times
 */
void FakeDaemon::testSensors(int times)
{
    qDebug() << "Testing sensors";
    for (int j = 0; j < times; j++)
    {
        for (int i = 0; i < fakeObservers.size(); i++)
        {
            fakeObservers[i]->subscribe();
            fakeObservers[i]->update();
            qDebug() << fakeObservers[i]->getName() << " = " << fakeObservers[i]->getValue();
            fakeObservers[i]->unsubscribe();
        }
    }
}

/**
 * @brief FakeDaemon::closeTelemetry
 */
void FakeDaemon::closeTelemetry()
{
    qDebug() << "TELEMETRY CLOSED";
    timer.stop();
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(zipPackage()));
    for (int i = 0; i < fakeObservers.size(); i++)
        fakeObservers[i]->unsubscribe();
}

/**
 * @brief FakeDaemon::notify
 */
void FakeDaemon::notify()
{
    for (int i = 0; i < fakeObservers.size(); i++)
        fakeObservers[i]->update();
}

/**
 * @brief FakeDaemon::attach
 * @param fakeObs
 */
void FakeDaemon::attach(FakeObserver *fakeObs)
{
    fakeObservers.push_back(fakeObs);
}

/**
 * @brief FakeDaemon::startTelemetry
 */
void FakeDaemon::startTelemetry()
{
    udpCommunicator->setHostAddr(tcpCommunicator->getHostAddress());
    qDebug() << udpCommunicator->getHostAddr().toString();
    tcpCommunicator->send(TelemetryConst::SEND_FROM_DAEMON_MESSAGE());
    qDebug() << "Telemetry started";
    timer.stop();
    connect(&timer, SIGNAL(timeout()), this, SLOT(zipPackage()));
    timer.start(updatePeriod);
}

/**
 * @brief FakeDaemon::zipPackage
 */
void FakeDaemon::zipPackage()
{
    QString package;
    QElapsedTimer elapsedTimer;
    QElapsedTimer cycleTimer;
    if (count == 1000)
    {
        qDebug() << count << "Packages with size" << pckgSize << "bytes send took "
                 << elapsedTimer.elapsed() - time << "milliseconds";
        count = 0;
        time = 0;
    }
    if (count == 0)
    {
        elapsedTimer.start();
    }
    for (int j = 0; j < int(pckgSize / 75); j++)
    {
        cycleTimer.start();
        for (int i = 0; i < fakeObservers.size(); i++)
        {
            QVector<float> data = fakeObservers[i]->getValue();
            QString dataString;
            for (int j = 0; j < data.size() - 1; j++)
                dataString += QString::number(data[j]) + "*";
            dataString += QString::number(data[data.size() - 1]) + ";";
            QString obsMessage = fakeObservers[i]->getName() + ":" + dataString;
            package += obsMessage;
            fakeObservers[i]->subscribe();
            fakeObservers[i]->update();
            fakeObservers[i]->unsubscribe();
        }
    }
    time += cycleTimer.elapsed();
    if (package.size() > 0)
    {
        package += QString::number(count);
        udpCommunicator->send(package);
    }
    count++;
}

/**
 * @brief FakeDaemon::parseMessage
 * @param message
 */
void FakeDaemon::parseMessage(QString message)
{
    qDebug() << message;
    QStringList list = message.split(":", QString::SkipEmptyParts);

    if (list.at(0).trimmed() == SUBSCRIBE_STRING)
    {
        for (int i = 0; i < fakeObservers.size(); i++)
        {
            if (fakeObservers[i]->getName() == list.at(1).trimmed())
            {
                fakeObservers[i]->subscribe();
            }
        }
    } else
    if (list.at(0).trimmed() == UNSUBSCRIBE_STRING)
    {
        for (int i = 0; i < fakeObservers.size(); i++)
        {
            if (fakeObservers[i]->getName() == list.at(1).trimmed())
            {
                fakeObservers[i]->unsubscribe();
            }
        }
    }
}
