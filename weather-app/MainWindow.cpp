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

void MainWindow::showDetailedWeatherPage(const QSharedPointer<WeatherData> &data)
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
