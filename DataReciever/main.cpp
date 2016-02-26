#include <QCoreApplication>
#include <communicator.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Communicator *cmtr = new Communicator();
    return a.exec();
}
