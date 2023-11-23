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

<<<<<<< HEAD
    QStackedWidget *stackedWidget = new QStackedWidget(this);

    HomePage *homePage = new HomePage();

    stackedWidget->addWidget(homePage);
    setCentralWidget(stackedWidget);

    // Optionally set HomePage as the initial page
    stackedWidget->setCurrentWidget(homePage);

    WeatherAPI *api = new WeatherAPI(this);

    QString location = QString::fromStdString("Belgrade"); // test

    for(int i = 0; i < 25; i++){
=======
    auto *api = new WeatherAPI(this);
    auto location = QString::fromStdString("Belgrade"); // test

    for(int i = 0; i < 1; i++){
>>>>>>> a8e521bed7d90ff0424c572b3ff02b4889206a40
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

<<<<<<< HEAD
=======
void MainWindow::addNewWidget(WeatherData* data) // test
{
    auto rightWidget = this->findChild<QWidget*>("widget");
    auto leftWidget = this->findChild<QWidget*>("widget_2");

    QVariant value = leftWidget->property("InsertWidget");

    bool insertLeftWidget = value.toBool();

    if(insertLeftWidget){
        WeatherWidget* tile = new WeatherWidget(leftWidget, data);
        this->m_widgets.push_back(tile);

        auto leftVBox = this->findChild<QVBoxLayout*>("verticalLayout_2");
        leftVBox->addWidget(tile);
        auto leftSpacer = new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
        leftVBox->addSpacerItem(leftSpacer);
    }
    else {
        WeatherWidget* tile = new WeatherWidget(rightWidget, data);
        this->m_widgets.push_back(tile);

        auto rightVBox = this->findChild<QVBoxLayout*>("verticalLayout_3");
        rightVBox->addWidget(tile);
        auto rightSpacer = new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
        rightVBox->addSpacerItem(rightSpacer);
    }
    leftWidget->setProperty("InsertWidget", !insertLeftWidget);
}


>>>>>>> a8e521bed7d90ff0424c572b3ff02b4889206a40
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
