#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QStackedWidget>

#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "HomePage.h"
#include "DetailedWeatherPage.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , homePage(new HomePage(this))
    , detailedWeather(new DetailedWeatherPage(this))
    , stackedWidget(new QStackedWidget(this))
{
    connect(this, &MainWindow::detailedWeatherPageShown, detailedWeather, &DetailedWeatherPage::setData);

    ui->setupUi(this);
    resize(900,600);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(detailedWeather);
    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(homePage);

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

void MainWindow::showDetailedWeatherPage(QSharedPointer<WeatherData> data)
{
    stackedWidget->setCurrentWidget(detailedWeather);
    emit detailedWeatherPageShown(data);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete homePage;
    delete detailedWeather;
    delete stackedWidget;
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
