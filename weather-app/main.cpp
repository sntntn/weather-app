#include "MainWindow.h"
#include "location.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Location l;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
