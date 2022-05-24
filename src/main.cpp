#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("AnythingToMusic");
    QCoreApplication::setOrganizationName("Microrofl");
    QCoreApplication::setOrganizationDomain("https://www.youtube.com/channel/UCzKqToAvJeIlj44b31yNs1g");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
