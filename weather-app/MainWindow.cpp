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
#include "Serializer.h"

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
    connect(this, &MainWindow::deletePageWidgets, homePage, &Page::deleteWidgets);
    connect(this, &MainWindow::deletePageWidgets, detailedWeather, &Page::deleteWidgets);
}

MainWindow::~MainWindow()
{
    delete ui;
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
{   //todo maybe? sta ce weatherapi njegova promenljiva GeoLocationData ako se njemu prosledjuju koordinate
    //ima veze sa parserom koji cemo izbrisati svakako
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

void MainWindow::closeEvent(QCloseEvent *event){
    serializeData();
    QMainWindow::closeEvent(event);
}

void MainWindow::serializeData(){
    Serializer::save(settings, "../Serialization/settings.json");
}
