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

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , homePage(new HomePage(this))
    , detailedWeather(new DetailedWeatherPage(this))
    , stackedWidget(new QStackedWidget(this))
    , userLocation(new UserLocation(this))
{
    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);
    connect(userLocation, &UserLocation::userLocationFetched, this, &MainWindow::fetchUserLocationData);

    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);
    stackedWidget->setCurrentWidget(homePage);

    // test
    QVector<QSharedPointer<GeoLocationData>> locations;
    for(int i = 0; i < 10; i++){
        QSharedPointer<GeoLocationData> data(new GeoLocationData("Belgrade", "", QGeoCoordinate(44.8125, 20.4375)));
        locations.emplaceBack(data);
    }

    for(auto &location : locations){
        auto *api = new WeatherAPI(location, this);

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

void MainWindow::fetchUserLocationData(const QSharedPointer<GeoLocationData> &data)
{
    qDebug() << data.data()->getCoordinates();
    auto *api = new WeatherAPI(data, this);
    connect(api, &ApiHandler::finished, api, &WeatherAPI::deleteLater);
    connect(api, &ApiHandler::dataFetched, homePage, &HomePage::addNewWidget);
    connect(api, &ApiHandler::dataFetched, detailedWeather, &DetailedWeatherPage::addNewWidget);
    api->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
