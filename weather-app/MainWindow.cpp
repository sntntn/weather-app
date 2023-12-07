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
#include "Settings.h"
#include "GeoLocationData.h"


#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(Settings::instance())
    , homePage(new HomePage(this))
    , detailedWeather(new DetailedWeatherPage(this))
    , stackedWidget(new QStackedWidget(this))
    , savedLocations(QVector<GeoLocationData>()) // todo serijalizacija
{
    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);
    connect(homePage, &HomePage::locationObjectSelected,this,&MainWindow::handleLocationObjectSelected);

    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);
    stackedWidget->setCurrentWidget(homePage);

    for(auto &location : settings.locationNames){
        savedLocations.append(GeoLocationData(location, location, QGeoCoordinate(44.8178, 20.4569)));
    }

    // TEST: tmp memory leak
//    auto location1 = GeoLocationData("Belgrade, City of Belgrade, Serbia", "Belgrade", QGeoCoordinate(44.8178, 20.4569));
//    auto location2 = GeoLocationData("Berlin, Germany", "Berlin", QGeoCoordinate(52.517, 12.3889));
//    auto location3 = GeoLocationData("Paris, Ile-de-France, France", "Paris", QGeoCoordinate(48.8589, 2.32004));
//    auto location4 = GeoLocationData("Athens, Central Athens, Greece", "Athens", QGeoCoordinate(37.9756,23.7348));
//    savedLocations.push_back(location1);
//    savedLocations.push_back(location2);
//    savedLocations.push_back(location3);
//    savedLocations.push_back(location4);

    getSavedLocationsData();
}

void MainWindow::getSavedLocationsData()
{
//    for(const auto &location : savedLocations){
//        getLocationData(location);
//    }
    for(const auto& location : settings.locationNames){
        getLocationData(GeoLocationData(location, location, QGeoCoordinate(44.8178, 20.4569)));
    }
}

void MainWindow::showHomePage(){
    stackedWidget->setCurrentWidget(homePage);
}

void MainWindow::showDetailedWeatherPage(const GeoLocationData &data) // todo sharedptr
{
    stackedWidget->setCurrentWidget(detailedWeather);
    emit detailedWeatherPageShown(data);
}

void MainWindow::refreshPages()
{
    connect(this, &MainWindow::deletePageWidgets, homePage, &Page::deleteWidgets);
    connect(this, &MainWindow::deletePageWidgets, detailedWeather, &Page::deleteWidgets);

    emit deletePageWidgets();
    getSavedLocationsData();
}

void MainWindow::saveNewLocation(const GeoLocationData& location) // todo sharedptr
{
    // todo serijalizacija
    savedLocations.push_back(location);
    getLocationData(location);
}

void MainWindow::getLocationData(const GeoLocationData &location) // todo sharedptr
{
    auto* api = new WeatherAPI(location, this);

    connect(api, &ApiHandler::finished, api, &WeatherAPI::deleteLater);
    connect(api, &ApiHandler::dataFetched, homePage, &HomePage::addNewWidget);
    connect(api, &ApiHandler::dataFetched, detailedWeather, &DetailedWeatherPage::addNewWidget);

    api->start();
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
    api->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
