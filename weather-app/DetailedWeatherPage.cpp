#include "DetailedWeatherPage.h"

#include <iostream>
#include "WeatherData.h"
#include "WeatherWidget.h"

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : QWidget{parent},
    m_locations(),
    mainLayout(new QHBoxLayout(this)),
    widgetsScrollArea(new QScrollArea()),
    weatherScrollArea(new QScrollArea()),
    widgetsScrollAreaContents(new QWidget()), // Container widget for the scroll area
    weatherScrollAreaContents(new QWidget()), // Container widget for the scroll area
    widgetsLayout(new QVBoxLayout()),
    weatherLayout(new QVBoxLayout())
{
    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);
    weatherScrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "    width: 7px;"
        "    border-radius: 30px;"  // Rounded corners for the scroll bar
        "}"
        "QScrollBar::handle:vertical {"
        "    background: gray;"
        "    min-height: 20px;"
        "    border-radius: 30px;"  // Rounded corners for the handle
        "}");
    mainLayout->addWidget(weatherScrollArea);


    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    widgetsScrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "    width: 7px;"
        "    border-radius: 30px;"  // Rounded corners for the scroll bar
        "}"
        "QScrollBar::handle:vertical {"
        "    background: gray;"
        "    min-height: 20px;"
        "    border-radius: 30px;"  // Rounded corners for the handle
        "}");
    mainLayout->addWidget(widgetsScrollArea);

}

void DetailedWeatherPage::setData(WeatherData* data) {
    if (data != nullptr) {
        std::cout << data->location.toStdString() << std::endl << data ->temperature << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}

void DetailedWeatherPage::getLocations(QVector<WeatherData*> locations){

    m_locations = locations;
    for(auto location : locations){
        std::cout << location->location.toStdString() << std::endl << location->temperature << std::endl;
    }
    drawWidgets(m_locations);
}

void DetailedWeatherPage::drawWidgets(QVector<WeatherData*> m_locations)
{
    for(auto data : m_locations){

        WeatherWidget* tile = new WeatherWidget(widgetsScrollAreaContents, data);
        tile->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        //connect(tile, &WeatherWidget::clicked, m_mainWindow, &MainWindow::onWeatherWidgetClicked);

        //this->m_widgets.push_back(tile);

        weatherLayout->addWidget(tile);
    }


}
