#include "DetailedWeatherPage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "GeoLocationData.h"
#include "Settings.h"

#include <iostream>

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : Page{parent}
    , data(*(new GeoLocationData("test", "test", QGeoCoordinate()))) // test, todo sharedptr (?)
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QGridLayout())
    , weatherLayout(new QGridLayout())
    , returnToHomePage(new QPushButton("< Home"))
    , horizontalSpacer(new QSpacerItem(spacerWidth, 0, QSizePolicy::Expanding, QSizePolicy::Minimum))
    , addToSavedLocations(new QPushButton("Add"))
    , scrollTimer(new QTimer(this))
    , selectedWidget(nullptr)
{
    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsLayout->setAlignment(Qt::AlignTop);

    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    widgetsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    weatherLayout->addWidget(returnToHomePage, 0, 0);
    weatherLayout->addItem(horizontalSpacer, 0, 1);
    weatherLayout->addWidget(addToSavedLocations, 0, 2);
    weatherLayout->setAlignment(Qt::AlignTop);

    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);

    mainLayout->addWidget(widgetsScrollArea);
    mainLayout->addWidget(weatherScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
    connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addButtonClicked);
    connect(this, &DetailedWeatherPage::locationSaved, this->mainWindow, &MainWindow::saveNewLocation);

    scrollTimer->setSingleShot(true);
    connect(scrollTimer, &QTimer::timeout, this, &DetailedWeatherPage::scrollToMaximum);
    connect(returnToHomePage, &QPushButton::clicked, this, &DetailedWeatherPage::afterHomeButtonPressed);
}

void DetailedWeatherPage::addNewWidget(const QSharedPointer<Data> &data)
{
    auto *widget = new WeatherWidget(qSharedPointerCast<WeatherData>(data), widgetsScrollAreaContents);
    connect(widget, &WeatherWidget::clicked, this, &DetailedWeatherPage::setData);

    widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    widget->setMaximumWidth(widgetsScrollArea->viewport()->width());

    int position = Settings::instance().savedLocations.indexOf(widget->data->location);
    widgetsLayout->addWidget(widget, position, 0, 1, 1);

    m_widgets.emplaceBack(widget);
}
void DetailedWeatherPage::scrollToWidget(const GeoLocationData& locationData)
{
    for (auto widget : m_widgets) {
        if (widget->data->location == locationData) {
            // Ponistimo prethodno odabrani widget
            if (selectedWidget) {
                selectedWidget->resetHighlight();
            }
            // Postavimo novi odabrani widget
            selectedWidget = widget;
            if (selectedWidget) {
                selectedWidget->setHighlighted();
            }

            // Pronasli smo widget -> pa pomeramo scroll bar na njegov položaj
            widgetsScrollArea->ensureWidgetVisible(widget);
            break;
        }
    }
}

void DetailedWeatherPage::setData(const GeoLocationData &data) // todo sharedptr
{
    this->data = data;
    // test
    std::cout << data.getRenamedPlace().toStdString() << " "
              << data.getCoordinates().toString().toStdString() << std::endl;

    // test, todo
    Settings::instance().savedLocations.indexOf(data) == -1 ? this->addToSavedLocations->setVisible(true)
                                                            : this->addToSavedLocations->setVisible(false);
}

void DetailedWeatherPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int newWidth = this->width() / 3;
    widgetsScrollArea->setFixedWidth(newWidth);
}

void DetailedWeatherPage::addButtonClicked()
{
    emit locationSaved(this->data);
    this->addToSavedLocations->setVisible(false);
    Settings::instance().savedLocations.push_back(this->data);

    scrollTimer->start(addButtonScrollTime);
}

void DetailedWeatherPage::scrollToMaximum()
{
    auto widgetsScrollBar = widgetsScrollArea->verticalScrollBar();
    widgetsScrollBar->setValue(widgetsScrollBar->maximum());
}

void DetailedWeatherPage::afterHomeButtonPressed() {
    auto widgetsScrollBar = widgetsScrollArea->verticalScrollBar();
    widgetsScrollBar->setValue(0);
    if (selectedWidget) {
        selectedWidget->resetHighlight();
    }
}
