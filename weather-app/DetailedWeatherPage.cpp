#include "DetailedWeatherPage.h"

#include <iostream>
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "MainWindow.h"

DetailedWeatherPage::DetailedWeatherPage(MainWindow *mainWindow, QWidget *parent)
    : QWidget{parent},
    m_locations(),
    m_mainWindow(mainWindow),
    mainLayout(new QHBoxLayout(this)),
    widgetsScrollArea(new QScrollArea()),
    weatherScrollArea(new QScrollArea()),
    widgetsScrollAreaContents(new QWidget()),
    weatherScrollAreaContents(new QWidget()),
    widgetsLayout(new QVBoxLayout()),
    weatherLayout(new QVBoxLayout()),
    returnToHomePage(new QPushButton()),
    addToSavedLocations(new QPushButton())
{

    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(widgetsScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, mainWindow, &MainWindow::onReturnToHomePageClicked);
    // TODO: add location button: connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addLocation);

    returnToHomePage->setText("< Home Page");
    addToSavedLocations->setText("Add");

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(returnToHomePage);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(addToSavedLocations);

    weatherLayout->setAlignment(Qt::AlignTop);
    weatherLayout->addLayout(buttonsLayout);

    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(weatherScrollArea);

}

void DetailedWeatherPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    int newWidth = this->width() / 3;
    widgetsScrollArea->setFixedWidth(newWidth);
}

void DetailedWeatherPage::setData(QString location) {
    if (location != nullptr) {
        std::cout << location.toStdString() << std::endl;
    }
}

void DetailedWeatherPage::getLocations(QVector<WeatherData*> locations){

    m_locations = locations;
    drawWidgets(m_locations);
}

void DetailedWeatherPage::setLocation(QString location){
    setData(location);
}

void DetailedWeatherPage::drawWidgets(QVector<WeatherData*> m_locations)
{
    for(auto data : m_locations){

        WeatherWidget* tile = new WeatherWidget(data, widgetsScrollAreaContents);

        // has to use setLocation slot to call setData because of calling setData from home page
        connect(tile, &WeatherWidget::clicked, this, &DetailedWeatherPage::setLocation);

        widgetsLayout->addWidget(tile);
    }
}

DetailedWeatherPage::~DetailedWeatherPage()
{
    delete m_mainWindow;
    delete mainLayout;
    delete widgetsScrollArea;
    delete weatherScrollArea;
    delete widgetsScrollAreaContents;
    delete weatherScrollAreaContents;
    delete widgetsLayout;
    delete weatherLayout;
    delete returnToHomePage;
    delete addToSavedLocations;

    for(auto location : m_locations){
        delete location;
    }
}
