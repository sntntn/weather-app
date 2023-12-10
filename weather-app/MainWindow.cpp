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
{
    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);
    stackedWidget->setCurrentWidget(homePage);

    getSavedLocationsData();

    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);
    // todo obrisati?
    connect(homePage, &HomePage::locationObjectSelected,this,&MainWindow::handleLocationObjectSelected);
    connect(this, &MainWindow::deletePageWidgets, homePage, &Page::deleteWidgets);
    connect(this, &MainWindow::deletePageWidgets, detailedWeather, &Page::deleteWidgets);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSavedLocationsData()
{
    for(const auto& location : settings.savedLocations){
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
    getSavedLocationsData();
}

// todo obrisati?
void MainWindow::handleLocationObjectSelected(const GeoLocationData& locationData)
{
    qDebug()<<"Location:" << locationData.getPlace()
            <<"Latitude:" << locationData.getCoordinates().latitude()
            <<"Longitude:" << locationData.getCoordinates().longitude();
    qDebug()<<"Default renamed place: " << locationData.getRenamedPlace();
    //mutableLocationData.setRenamedPlace("Moj Rodni Grad");
    qDebug()<<"after renaming - renamed place: " << locationData.getRenamedPlace();
}
