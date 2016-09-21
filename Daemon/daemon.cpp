#include <QDebug>
#include <QStringList>
#include "brickFactory.h"
#include "daemon.h"

using namespace trikControl;

Daemon::Daemon(QThread *guiThread, QString configPath) :
    brick(trikControl::BrickFactory::create())

{
    updatePeriod = TCP_PEDIOD;
    tcpCommunicator = new TcpCommunicator();
    udpCommunicator = new UdpCommunicator();
    tcpCommunicator->setPort(START_PORT_INT);
    udpCommunicator->setPort(START_PORT_INT);
    tcpCommunicator->listen();
    connect(tcpCommunicator, SIGNAL(newConnection()), this, SLOT(startTelemetry()));
    connect(tcpCommunicator, SIGNAL(recieveMessage(QString)), this, SLOT(parseMessage(QString)));
    connect(tcpCommunicator, SIGNAL(lostConnection()), this, SLOT(closeTelemetry()));

    gyroObserver = new GyroObserver(GYROSCOPE_NAME, brick, this);
    gyroObserver->setUpdateInterval(SENSORS3D_DATA_UPDATE_PERIOD);
    accelObserver = new AccelObserver(ACCELEROMETER_NAME, brick, this);
    accelObserver->setUpdateInterval(SENSORS3D_DATA_UPDATE_PERIOD);
    batteryObserver = new BatteryObserver(BATTERY_NAME, brick, this);
    batteryObserver->setUpdateInterval(BATTERY_DATA_UPDATE_PERIOD);

    qDebug() << brick->motorPorts(MotorInterface::Type::powerMotor);
    qDebug() << brick->encoderPorts();

    powerMotor1 = new PowerMotorObserver(POWER_MOTOR1_NAME, brick, this);
    powerMotor1->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);
    powerMotor2 = new PowerMotorObserver(POWER_MOTOR2_NAME, brick, this);
    powerMotor2->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);
    powerMotor3 = new PowerMotorObserver(POWER_MOTOR3_NAME, brick, this);
    powerMotor3->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);
    powerMotor4 = new PowerMotorObserver(POWER_MOTOR4_NAME, brick, this);
    powerMotor4->setUpdateInterval(MOTOR_DATA_UPDATE_PERIOD);

    encoder1 = new EncoderObserver(ENCODER1_NAME, brick, this);
    encoder1->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);
    encoder2 = new EncoderObserver(ENCODER2_NAME, brick, this);
    encoder2->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);
    encoder3 = new EncoderObserver(ENCODER3_NAME, brick, this);
    encoder3->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);
    encoder4 = new EncoderObserver(ENCODER4_NAME, brick, this);
    encoder4->setUpdateInterval(ENCODER_DATA_UPDATE_PERIOD);

    for (int i = 0; i < observers.size(); i++)
        qDebug() << observers[i]->getName();

    testSensors(2);
}

void Daemon::testSensors(int times)
{
    for (int j = 0; j < times; j++)
    {
        for (int i = 0; i < observers.size(); i++)
        {
            observers[i]->subscribe();
            observers[i]->update();
            qDebug() << observers[i]->getName() << " = " << observers[i]->getValue();
            observers[i]->unsubscribe();
        }
    }
}

void Daemon::closeTelemetry()
{
    qDebug() << "TELEMETRY CLOSED";
    timer.stop();
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(zipPackage()));
    for (int i = 0; i < observers.size(); i++)
        observers[i]->unsubscribe();
    delete(udpCommunicator);
    delete(tcpCommunicator);
    delete(&observers);
}

void Daemon::notify()
{
    for (int i = 0; i < observers.size(); i++)
        observers[i]->update();
}

void Daemon::attach(Observer *obs)
{
    observers.push_back(obs);
}

void Daemon::startTelemetry()
{
    tcpCommunicator->send(TelemetryConst::SEND_FROM_DAEMON_MESSAGE());
    udpCommunicator->setHostAddr(tcpCommunicator->getHostAddress());
    timer.stop();
    connect(&timer, SIGNAL(timeout()), this, SLOT(zipPackage()));
    timer.start(updatePeriod);
    for (int i = 0; i < observers.size(); i++)
        observers[i]->subscribe();
}

void Daemon::zipPackage()
{
    QString package;
    for (int i = 0; i < observers.size(); i++)
    {
         QVector<float> data = observers[i]->getValue();
         QString dataString;
         for (int j = 0; j < data.size() - 1; j++)
            dataString += QString::number(data[j]) + "*";
         dataString += QString::number(data[data.size() - 1]) + ";";
         QString obsMessage = observers[i]->getName() + ":" + dataString;
         package += obsMessage;
    }
    if (package.size() > 0)
    {
        tcpCommunicator->send(package);
    }
}

const void Daemon::parseMessage(QString message) const
{
    qDebug() << message;
    QStringList list = message.split(":", QString::SkipEmptyParts);

    if (list.at(0).trimmed() == SUBSCRIBE_STRING)
    {
        for (int i = 0; i < observers.size(); i++)
        {
            if (observers[i]->getName() == list.at(1).trimmed())
            {
                observers[i]->subscribe();
            }
        }
    } else
    if (list.at(0).trimmed() == UNSUBSCRIBE_STRING)
    {
        for (int i = 0; i < observers.size(); i++)
        {
            if (observers[i]->getName() == list.at(1).trimmed())
            {
                observers[i]->unsubscribe();
            }
        }
    }
}
