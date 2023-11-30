#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QStackedWidget>

#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "HomePage.h"
#include "DetailedWeatherPage.h"
#include "geocodingapi.h"

#include <iostream>

GeocodingAPI geocodingApi;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , homePage(new HomePage(this))
    , detailedWeather(new DetailedWeatherPage(this))
    , stackedWidget(new QStackedWidget(this))
{
    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);
    connect(&geocodingApi, &GeocodingAPI::geocodingDataUpdated, this, &MainWindow::updateGeocodingData);


    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(homePage);


    geocodingApi.testCityFunction("Belgrade");
    qDebug()<< "---> " <<"Latitude:" << m_lastLatitude << "Longitude:" << m_lastLongitude;



    QVector<QString> locations(3, "Belgrade"); // test

    for(auto location : locations){
        auto* api = new WeatherAPI(location, this);
        connect(api, &WeatherAPI::finished, api, &WeatherAPI::deleteLater);
        connect(api, &WeatherAPI::dataFetched, homePage, &HomePage::addNewWidget);
        connect(api, &WeatherAPI::dataFetched, detailedWeather, &DetailedWeatherPage::addNewWidget);

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

void MainWindow::updateGeocodingData(const QString &place, double latitude, double longitude){
    qDebug() << "City:" << place << "Latitude:" << latitude << "Longitude:" << longitude;
    m_lastLatitude=latitude;
    m_lastLongitude=longitude;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete homePage;
    delete detailedWeather;
    delete stackedWidget;
}
