#include "MainWindow.h"
#include "location.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Location l;
    MainWindow w;
    w.show();
    return a.exec();
}
