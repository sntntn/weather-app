#include "DetailedWeatherPage.h"

#include <iostream>

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"

DetailedWeatherPage::DetailedWeatherPage(MainWindow *mainWindow, QWidget *parent)
    : QWidget{parent}
    , m_mainWindow(mainWindow)
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QVBoxLayout())
    , weatherLayout(new QVBoxLayout())
    , buttonsLayout(new QHBoxLayout())
    , returnToHomePage(new QPushButton())
    , addToSavedLocations(new QPushButton())
{

    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(widgetsScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, mainWindow, &MainWindow::onReturnToHomePageClicked);
    // TODO: add location button: connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addLocation);

    returnToHomePage->setText("< Home Page");
    addToSavedLocations->setText("Add");

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

void DetailedWeatherPage::setData(const QString& location) {
    if (location != nullptr) {
        //std::cout << location.toStdString() << std::endl;
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

        auto tile = new WeatherWidget(data, widgetsScrollAreaContents);
        this->m_widgets.append(tile);

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
    delete buttonsLayout;
    delete returnToHomePage;
    delete addToSavedLocations;

    for(auto widget : m_widgets){
        delete widget;
    }
    for(auto location : m_locations){
        delete location;
    }
}
