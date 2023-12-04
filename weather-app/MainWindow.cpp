#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QStackedWidget>

#include "ApiHandler.h"
#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "HomePage.h"
#include "DetailedWeatherPage.h"
#include "geocodingapi.h"
#include "GeoLocationData.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , homePage(new HomePage(this))
    , detailedWeather(new DetailedWeatherPage(this))
    , stackedWidget(new QStackedWidget(this))
{
    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);
    connect(homePage, &HomePage::locationObjectSelected,this,&MainWindow::handleLocationObjectSelected);

    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(homePage);

    QVector<QString> locations(3, "Belgrade"); // test

    for(auto location : locations){
        auto* api = new WeatherAPI(location, this);
        connect(api, &ApiHandler::finished, api, &WeatherAPI::deleteLater);

        connect(api, &ApiHandler::dataFetched, homePage, &HomePage::addNewWidget);
        connect(api, &ApiHandler::dataFetched, detailedWeather, &DetailedWeatherPage::addNewWidget);

        api->start();
    }


}

void MainWindow::showHomePage(){
    stackedWidget->setCurrentWidget(homePage);
}

void MainWindow::showDetailedWeatherPage(const QSharedPointer<WeatherData> &data)
{
    stackedWidget->setCurrentWidget(detailedWeather);
    emit detailedWeatherPageShown(data);
}

void MainWindow::handleLocationObjectSelected(const GeoLocationData& locationData)
{
    GeoLocationData mutableLocationData = locationData;     //da bih zadrzao const i referencu na signalu - stabilniji prenos
    qDebug()<<"Location:" << mutableLocationData.getPlace()
             << "Latitude:"<< mutableLocationData.getCoordinates().latitude()
             << "Longitude:" << mutableLocationData.getCoordinates().longitude();
    qDebug()<< "Default renamed place: " <<mutableLocationData.getRenamedPlace();
    mutableLocationData.setRenamedPlace("Moj Rodni Grad");
    qDebug()<< "after renaming - renamed place: " <<mutableLocationData.getRenamedPlace();

}

MainWindow::~MainWindow()
{
    delete ui;
}
