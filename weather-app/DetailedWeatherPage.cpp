#include "DetailedWeatherPage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "GeoLocationData.h"
#include "Settings.h"
#include "DetailedWeatherAPI.h"
#include "DetailedWeatherData.h"

#include <iostream>

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : Page{parent}
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QGridLayout())
    , weatherLayout(new QVBoxLayout())
    , buttonsLayout(new QHBoxLayout())
    , returnToHomePage(new QPushButton("< Home"))
    , horizontalSpacer(new QSpacerItem(spacerWidth, 0, QSizePolicy::Expanding, QSizePolicy::Minimum))
    , addToSavedLocations(new QPushButton("Add"))
    , scrollTimer(new QTimer(this))
    , locationLabel(new QLabel(this))
    , temperatureLabel(new QLabel(this))
    , minmaxTemperature(new QLabel(this))
    , selectedWidget(nullptr)
{
    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsLayout->setAlignment(Qt::AlignTop);

    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    widgetsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    buttonsLayout->addWidget(returnToHomePage);
    buttonsLayout->addItem(horizontalSpacer);
    buttonsLayout->addWidget(addToSavedLocations);

    weatherLayout->setAlignment(Qt::AlignTop);
    weatherLayout->addLayout(buttonsLayout);

    locationLabel->setStyleSheet("font-size: 24px;");
    temperatureLabel->setStyleSheet("font-size: 48px; font-weight: bold;");
    minmaxTemperature->setStyleSheet("font-size: 16px;");

    weatherLayout->addWidget(locationLabel, 0, Qt::AlignHCenter);
    weatherLayout->addWidget(temperatureLabel, 0, Qt::AlignHCenter);
    weatherLayout->addWidget(minmaxTemperature, 0, Qt::AlignHCenter);

    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);

    mainLayout->addWidget(widgetsScrollArea);
    mainLayout->addWidget(weatherScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
    connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addButtonClicked);
    connect(this, &DetailedWeatherPage::locationSaved, this->mainWindow, &MainWindow::saveNewLocation);

    connect(returnToHomePage, &QPushButton::clicked, this, &DetailedWeatherPage::afterHomePressed);
}

void DetailedWeatherPage::addNewWidget(const QSharedPointer<Data> &data)
{
    auto *widget = new WeatherWidget(qSharedPointerCast<WeatherData>(data), widgetsScrollAreaContents);
    connect(widget, &WeatherWidget::clicked, this, &DetailedWeatherPage::setData);

    widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    widget->setMaximumWidth(widgetsScrollArea->viewport()->width());

    int position = static_cast<int>(Settings::instance().savedLocations().indexOf(widget->data->location()));
    widgetsLayout->addWidget(widget, position, 0, 1, 1);

    m_widgets.emplaceBack(widget);
    scrollToMaximum();
}

void DetailedWeatherPage::setData(const GeoLocationData &data) // todo sharedptr
{
    this->data = data;

    Settings::instance().savedLocations().indexOf(data) == -1 ? this->addToSavedLocations->setVisible(true)
                                                            : this->addToSavedLocations->setVisible(false);

    highlightWidget();

    //isto ko za MainWindow, saljemo data da postavi a onda u fetchData saljemo koordinate
    auto* api = new DetailedWeatherAPI(data, this);
    //todo ceo data umesto koordinata
    api->fetchData(data.getCoordinates());
    connect(api, &DetailedWeatherAPI::dataFetched, this, &DetailedWeatherPage::showData);
}

void DetailedWeatherPage::showData(const QSharedPointer<Data> &data){
    //todo kad dobijemo novi izgled da se menja, DetailedWeatherPage da ima promenljvu svoju DetailedWeatherData?
    auto detailedData = qSharedPointerDynamicCast<DetailedWeatherData>(data);

    locationLabel->setText(detailedData->location.getRenamedPlace());
    temperatureLabel->setText(QString::number(detailedData->temperature) + "°");
    minmaxTemperature->setText("H:" + QString::number(detailedData->weeklyMaxTemp[0]) + "°  L:"
                               + QString::number(detailedData->weeklyMinTemp[0]) + "°");
}

void DetailedWeatherPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int newWidth = this->width() / 3;
    widgetsScrollArea->setFixedWidth(newWidth);
}

void DetailedWeatherPage::addButtonClicked()
{
    //placeholder za mesto gde je add button ili da se postavi na ignored umesto visibility false
    emit locationSaved(this->data);
    this->addToSavedLocations->setVisible(false);
    Settings::instance().savedLocations().push_back(this->data);
}

void DetailedWeatherPage::highlightWidget()
{
    if(selectedWidget){
        selectedWidget->resetHighlight();
    }
    for(auto *widget : m_widgets){
        if(widget->data->location() == this->data){
            widgetsScrollArea->ensureWidgetVisible(widget);
            selectedWidget = widget;
            if(selectedWidget){
                selectedWidget->setHighlight();
            }
        }
    }
}

void DetailedWeatherPage::scrollToMaximum()
{
    auto *widgetsScrollBar = widgetsScrollArea->verticalScrollBar();
    widgetsScrollBar->setValue(widgetsScrollBar->maximum());
}

void DetailedWeatherPage::afterHomePressed()
{
    widgetsScrollArea->verticalScrollBar()->setValue(0);
    if(selectedWidget){
        selectedWidget->resetHighlight();
    }
    selectedWidget = nullptr;
}
