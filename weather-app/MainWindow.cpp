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
