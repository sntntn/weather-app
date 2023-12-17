#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QStackedWidget>
#include <QGeoPositionInfoSource>

#include "ApiHandler.h"
#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "HomePage.h"
#include "DetailedWeatherPage.h"
#include "geocodingapi.h"
#include "UserLocation.h"
#include "Settings.h"
#include "GeoLocationData.h"
#include "Serializer.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(Settings::instance())
    , homePage(new HomePage(this))
    , detailedWeather(new DetailedWeatherPage(this))
    , stackedWidget(new QStackedWidget(this))
    , userLocation(new UserLocation(this))
{
    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);
    stackedWidget->setCurrentWidget(homePage);

    requestUserLocationData();
    getSavedLocationsData();

    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);
    connect(this, &MainWindow::deletePageWidgets, homePage, &Page::deleteWidgets);
    connect(this, &MainWindow::deletePageWidgets, detailedWeather, &Page::deleteWidgets);
    connect(userLocation, &UserLocation::userLocationFetched, this, &MainWindow::getLocationData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::requestUserLocationData()
{
    if(settings.shareLocation())
        userLocation->getLocation();
}

void MainWindow::getSavedLocationsData()
{
    for(const auto& location : settings.savedLocations()){
        getLocationData(location);
    }
}

void MainWindow::saveNewLocation(const GeoLocationData& location) // todo sharedptr
{
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
    emit deletePageWidgets();
    requestUserLocationData();
    getSavedLocationsData();
}

void MainWindow::closeEvent(QCloseEvent *event){
    serializeData();
    QMainWindow::closeEvent(event);
}

void MainWindow::serializeData(){
    Serializer::save(settings, "../Serialization/settings.json");
}
