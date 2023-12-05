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

    //TEST
    QVector<GeoLocationData> locations;
    GeoLocationData belgradeLocation1("Belgrade, City of Belgrade, Serbia", "Belgrade", QGeoCoordinate(44.8178, 20.4569));
    GeoLocationData belgradeLocation2("Berlin, Germany", "Berlin", QGeoCoordinate(52.517, 12.3889));
    GeoLocationData belgradeLocation3("Paris, Ile-de-France, France", "Paris", QGeoCoordinate(48.8589, 2.32004));
    GeoLocationData belgradeLocation4("Athens, Central Athens, Greece", "Athens", QGeoCoordinate(37.9756,23.7348));
    locations.append(belgradeLocation1);
    locations.append(belgradeLocation2);
    locations.append(belgradeLocation3);
    locations.append(belgradeLocation4);

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
    //mutableLocationData.setRenamedPlace("Moj Rodni Grad");
    qDebug()<< "after renaming - renamed place: " <<mutableLocationData.getRenamedPlace();

    auto* api = new WeatherAPI(mutableLocationData, this);
    connect(api, &ApiHandler::finished, api, &WeatherAPI::deleteLater);

    connect(api, &ApiHandler::dataFetched, homePage, &HomePage::addNewWidget);
    connect(api, &ApiHandler::dataFetched, detailedWeather, &DetailedWeatherPage::addNewWidget);

    api->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}
