#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <iostream>

#include <QStackedWidget>

#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "HomePage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStackedWidget *stackedWidget = new QStackedWidget(this);

    HomePage *homePage = new HomePage();

    stackedWidget->addWidget(homePage);
    setCentralWidget(stackedWidget);

    // Optionally set HomePage as the initial page
    stackedWidget->setCurrentWidget(homePage);

    auto *api = new WeatherAPI(this);
    auto location = QString::fromStdString("Belgrade"); // test

    for(int i = 0; i < 25; i++){
        api->fetchData(location);
    }

    connect(api, &WeatherAPI::dataFetched, homePage, &HomePage::addNewWidget);

}

MainWindow::~MainWindow()
{
    delete ui;

    for(auto widget : m_widgets){
        delete widget;
    }
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
