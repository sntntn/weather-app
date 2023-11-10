#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <iostream>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "WeatherAPI.h"
#include "WeatherData.h"
#include "WeatherWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    WeatherAPI *api = new WeatherAPI(this);

    QString location = QString::fromStdString("Belgrade"); // test
    api->fetchData(location);

    connect(api, &WeatherAPI::dataFetched, this, &MainWindow::addNewWidget);
}

MainWindow::~MainWindow()
{
    delete ui;

    for(auto widget : m_widgets){
        delete widget;
    }
}

void MainWindow::addNewWidget(WeatherData* data) // test
{
    auto leftWidget = this->findChild<QWidget*>("widget_2");
    WeatherWidget* tile = new WeatherWidget(leftWidget, data);
    tile->setFixedSize(leftWidget->width(), 80);
    this->m_widgets.push_back(tile);

    auto leftVBox = this->findChild<QVBoxLayout*>("verticalLayout_2");
    leftVBox->addWidget(tile);
    auto leftSpacer = new QSpacerItem(0, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftVBox->addSpacerItem(leftSpacer);
}

