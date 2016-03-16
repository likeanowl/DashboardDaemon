#include "dashboard.h"
#include "tcpcommunicator.h"
#include "udpcommunicator.h"
#include "parser.h"
#include <QApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Parser *parser = new Parser();
    UdpCommunicator *udpCommunicator = new UdpCommunicator(parser);
    TcpCommunicator *tcpCommunicator = new TcpCommunicator(parser);
    Dashboard dashboard(tcpCommunicator, udpCommunicator);

    return app.exec();
}
