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
    , weatherLayout(new QVBoxLayout())
    , buttonsLayout(new QHBoxLayout())
    , returnToHomePage(new QPushButton())
    , addToSavedLocations(new QPushButton())
{
    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(widgetsScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
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

    for(auto *widget : m_widgets){
        delete widget;
    }
}
