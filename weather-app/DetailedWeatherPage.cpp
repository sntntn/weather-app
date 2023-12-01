#include "DetailedWeatherPage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"

#include <iostream>

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : Page{parent}
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QVBoxLayout())
    , weatherLayout(new QGridLayout())
    , returnToHomePage(new QPushButton())
    , horizontalSpacer(new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum))
    , addToSavedLocations(new QPushButton())
{
    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(widgetsScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
    // TODO: add location button: connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addLocation);

    returnToHomePage->setText("< Home");
    addToSavedLocations->setText("Add");

    weatherLayout->addWidget(returnToHomePage, 0, 0);
    weatherLayout->addItem(horizontalSpacer, 0, 1);
    weatherLayout->addWidget(addToSavedLocations, 0, 2);

    weatherLayout->setAlignment(Qt::AlignTop);
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

void DetailedWeatherPage::addNewWidget(const QSharedPointer<Data> &data)
{
    auto *widget = new WeatherWidget(qSharedPointerCast<WeatherData>(data), widgetsScrollAreaContents);
    connect(widget, &WeatherWidget::clicked, this, &DetailedWeatherPage::setData);
    m_widgets.push_back(widget);

    widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    widgetsLayout->addWidget(widget);
}

void DetailedWeatherPage::setData(const QSharedPointer<WeatherData> &data)
{
    std::cout << data->location.toStdString() << std::endl;
}

DetailedWeatherPage::~DetailedWeatherPage()
{
    for(auto *widget : m_widgets){
        delete widget;
    }
}
