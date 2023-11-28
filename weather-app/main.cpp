#include "MainWindow.h"
#include "location.h"

#include <QApplication>
//#include "geocodingapi.h"


int main(int argc, char *argv[])
{
    Location l;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //GeocodingAPI geocodingApi;
    //geocodingApi.testCityFunction();

    return a.exec();
}
