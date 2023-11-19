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

    for(int i = 0; i < 5; i++){
        api->fetchData(location);
    }

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

