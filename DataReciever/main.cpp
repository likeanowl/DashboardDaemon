#include <QCoreApplication>
#include <communicator.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Communicator cmtr;
    cmtr.bindSocket();
    cmtr.send("Hello");
    return a.exec();
}
