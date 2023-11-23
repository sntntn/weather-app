#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <iostream>

#include <QStackedWidget>

#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "HomePage.h"
#include "DetailedWeatherPage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);

    homePage = new HomePage(this);
    detailedWeather = new DetailedWeatherPage();

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);

    // Optionally set HomePage as the initial page
    stackedWidget->setCurrentWidget(homePage);

    auto *api = new WeatherAPI(this);
    auto location = QString::fromStdString("Belgrade"); // test

    for(int i = 0; i < 25; i++){
        api->fetchData(location);
    }

    connect(api, &WeatherAPI::dataFetched, this, &MainWindow::addNewWidget);

}

void MainWindow::onWeatherWidgetClicked(WeatherData* data) {

    // Assuming you have a method in DetailedWeatherPage to set the data
    detailedWeather->setData(data);
    detailedWeather->getLocations(m_locations);

    // And assuming you have a member variable or a method to get the QStackedWidget
    stackedWidget->setCurrentWidget(detailedWeather);
}

MainWindow::~MainWindow()
{
    delete ui;

    for(auto location : m_locations){
        delete location;
    }
}

void MainWindow::addNewWidget(WeatherData* data){
    m_locations.append(data);
    homePage->addNewWidget(data);
}

/*
void MainWindow::geocodeCity(const QString& cityName)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleGeocodingResponse);

    QString apiUrl = QString("https://api.opencagedata.com/geocode/v1/json?q=%1&key=%2")
                         .arg(cityName)
                         .arg(OPEN_CAGE_API_KEY);

    QNetworkRequest request(QUrl(apiUrl));
    manager->get(request);
}

void MainWindow::handleGeocodingResponse(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }

    QByteArray responseData = reply->readAll();
    // Obrada JSON odgovora i izdvojavanje latitude i longitude
    // ...

    reply->deleteLater();
}

void MainWindow::someFunction()
{
    QString cityName = "Belgrade";  // za pocetak za Beograd
    geocodeCity(cityName);
}
*/
