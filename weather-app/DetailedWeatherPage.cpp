#include "DetailedWeatherPage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "GeoLocationData.h"
#include "Settings.h"
#include "DetailedWeatherAPI.h"
#include "DetailedWeatherData.h"

#include <iostream>
#include <QStackedWidget>
#include <QTimer>
#include <QPainter>
#include <QTransform>

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : Page{parent}
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QGridLayout())
    , weatherLayout(new QVBoxLayout())
    , basicInfoLayout(new QHBoxLayout())
    , leftBasicInfo(new QVBoxLayout())
    , rightBasicInfo(new QVBoxLayout())
    , buttonsLayout(new QHBoxLayout())
    , returnToHomePage(new QPushButton("< Home"))
    , horizontalSpacer(new QSpacerItem(spacerWidth, 0, QSizePolicy::Expanding, QSizePolicy::Minimum))
    , addToSavedLocations(new QPushButton("Add"))
    , scrollTimer(new QTimer(this))
    , locationLabel(new QLabel(this))
    , temperatureLabel(new QLabel(this))
    , minmaxTemperature(new QLabel(this))
    , weatherDescriptionLabel(new QLabel(this))
    , iconLabel(new QLabel(this))
    , weatherIcon(new QPixmap())
    , dateLabel(new QLabel(this))
    , timeLabel(new QLabel(this))
    , feelsLikeLabel(new QLabel(this))
    , compassLabel(new QLabel(this))
    , initialCompassIcon(new QPixmap("../Resources/compass/whiteCompass.png"))
    , arrowIcon(new QPixmap("../Resources/compass/whiteArrow.png"))
    , hourlyWeatherArea(new QScrollArea())
    , hourlyWeatherContents(new QWidget())
    , hourlyLayout(new QHBoxLayout())
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

    locationLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    leftBasicInfo->addWidget(iconLabel, 0, Qt::AlignLeft);
    leftBasicInfo->addWidget(weatherDescriptionLabel, 0, Qt::AlignLeft);
    leftBasicInfo->addWidget(dateLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
    leftBasicInfo->addWidget(timeLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    rightBasicInfo->addWidget(temperatureLabel, 0, Qt::AlignHCenter);
    rightBasicInfo->addWidget(feelsLikeLabel, 0, Qt::AlignRight | Qt::AlignTop);
    basicInfoLayout->addLayout(leftBasicInfo);
    basicInfoLayout->addLayout(rightBasicInfo);

    temperatureLabel->setStyleSheet("font-size: 100px; font-weight: bold;");
    minmaxTemperature->setStyleSheet("font-size: 16px;");

    //todo magic number 24
    for(int i = 0; i < 24; i++){
        HourlyWeatherWidget *widget = new HourlyWeatherWidget(this);
        widget->setFixedSize(70, 100);
        hourlyLayout->addWidget(widget);
    }

    hourlyWeatherContents->setFixedHeight(100);
    hourlyWeatherContents->setLayout(hourlyLayout);
    hourlyWeatherArea->setWidget(hourlyWeatherContents);
    hourlyWeatherArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    weatherLayout->addWidget(locationLabel, 0, Qt::AlignHCenter);
    weatherLayout->addLayout(basicInfoLayout);
    weatherLayout->addWidget(minmaxTemperature, 0, Qt::AlignHCenter);
    weatherLayout->addWidget(hourlyWeatherArea);
    weatherLayout->addWidget(compassLabel);

    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);

    mainLayout->addWidget(widgetsScrollArea);
    mainLayout->addWidget(weatherScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
    connect(returnToHomePage, &QPushButton::clicked, this, &DetailedWeatherPage::homeButtonClicked);
    connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addButtonClicked);
    connect(this, &DetailedWeatherPage::locationSaved, this->mainWindow, &MainWindow::saveNewLocation);
}

void DetailedWeatherPage::addNewWidget(const QSharedPointer<Data> &data)
{
    QSharedPointer<WeatherData> weatherData = qSharedPointerCast<WeatherData>(data);

    auto *widget = new WeatherWidget(weatherData, widgetsScrollAreaContents);
    connect(widget, &WeatherWidget::clicked, this, &DetailedWeatherPage::setData);

    widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    widget->setMaximumWidth(widgetsScrollArea->viewport()->width());

    int position = static_cast<int>(Settings::instance().savedLocations().indexOf(widget->data->location()));

    if(Settings::instance().shareLocation())
        position++;

    position == -1 ? widgetsLayout->addWidget(widget, 0, 0, 1, 1) // User location widget
                   : widgetsLayout->addWidget(widget, position, 0, 1, 1);

    m_widgets.emplaceBack(widget);

    QStackedWidget* stackedWidget = qobject_cast<QStackedWidget*>(this->parent());
    if (stackedWidget->currentWidget() == this) {
        QTimer::singleShot(100, this, &DetailedWeatherPage::highlightWidget);
    }
}

void DetailedWeatherPage::setData(const GeoLocationData &data) // todo sharedptr
{
    widgetsScrollArea->verticalScrollBar()->setValue(0);

    bool showAddbutton = data.getRenamedPlace() != "My location" &&
                         Settings::instance().savedLocations().indexOf(data) == -1;

    showAddbutton ? this->addToSavedLocations->setVisible(true)
                  : this->addToSavedLocations->setVisible(false);

    //isto ko za MainWindow, saljemo data da postavi a onda u fetchData saljemo koordinate
    auto* api = new DetailedWeatherAPI(data, this);
    //todo ceo data umesto koordinata
    api->fetchData(data.getCoordinates());
    connect(api, &DetailedWeatherAPI::dataFetched, this, &DetailedWeatherPage::showData);
}

void DetailedWeatherPage::showData(const QSharedPointer<Data> &data){
    //todo kad dobijemo novi izgled da se menja, DetailedWeatherPage da ima promenljvu svoju DetailedWeatherData?
    QSharedPointer<DetailedWeatherData> detailedData = qSharedPointerCast<DetailedWeatherData>(data);
    this->data = detailedData;
    highlightWidget();

    locationLabel->setText(detailedData->location.getRenamedPlace());
    //todo (need country from api)countryLabel->setText(detailedData->location.get)
    weatherIcon->load(Settings::instance().weatherCodeToIcon(detailedData->weatherCode, detailedData->isDay));
    iconLabel->setPixmap(weatherIcon->scaled(iconWidth, iconHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedWidth(iconWidth);

    weatherDescriptionLabel->setText(weatherCodeToDescription(detailedData->weatherCode));
    dateLabel->setText(QDateTime::currentDateTime().toTimeZone(detailedData->timezone).toString("'Today,' MMMM d") +
                       getDaySuffix(QDateTime::currentDateTime().toTimeZone(detailedData->timezone).date().day()));
    timeLabel->setText(QDateTime::currentDateTime().toTimeZone(detailedData->timezone).toString("HH:mm"));

    temperatureLabel->setText(QString::number(detailedData->temperature) + "°");
    feelsLikeLabel->setText("Feels like: " + QString::number(detailedData->apparentTemperature) + "°");

    minmaxTemperature->setText("H:" + QString::number(detailedData->weeklyMaxTemp[0]) + "°  L:"
                               + QString::number(detailedData->weeklyMinTemp[0]) + "°");

    for (int i = 0; i < hourlyLayout->count(); ++i) {
        QLayoutItem* item = hourlyLayout->itemAt(i);
        HourlyWeatherWidget* widget = dynamic_cast<HourlyWeatherWidget*>(item->widget());
        widget->updateData(this->data->hourlyTemperature[i], this->data->hourlyCode[i],
                           this->data->hourlyIsDay[i], this->data->hourlyTimeStamp[i]);
    }

    QPixmap compassIcon = initialCompassIcon->copy();
    QPainter painter(&compassIcon);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPoint center(compassIcon.width() / 2, compassIcon.height() / 2);

    painter.translate(center);
    painter.rotate(detailedData->windDirection - 180);
    painter.translate(-center);

    painter.drawPixmap(center.x() - arrowIcon->width() / 2,
                       center.y() - arrowIcon->height() / 2,
                       *arrowIcon);

    painter.end();

    compassLabel->setPixmap(compassIcon.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
    Settings::instance().savedLocations().push_back(this->data->location);
}

void DetailedWeatherPage::homeButtonClicked()
{
    if(selectedWidget){
        selectedWidget->resetHighlight();
    }

    selectedWidget = nullptr;
}

void DetailedWeatherPage::highlightWidget()
{
    if(selectedWidget){
        selectedWidget->resetHighlight();
    }

    auto newSelectedWidget = std::find_if(m_widgets.begin(), m_widgets.end(), [this](const auto* widget) {
        return widget->data->location() == this->data->location;
    });

    if (newSelectedWidget != m_widgets.end()) {
        selectedWidget = *newSelectedWidget;
        widgetsScrollArea->ensureWidgetVisible(selectedWidget);
        selectedWidget->setHighlight();
    }
}

DetailedWeatherPage::HourlyWeatherWidget::HourlyWeatherWidget(QWidget *parent)
    : QWidget(parent)
    , hourLayout(new QVBoxLayout(this))
    , hourLabel(new QLabel())
    , hourWeatherIcon(new QPixmap())
    , hourWeatherIconLabel(new QLabel(this))
    , hourTempLabel(new QLabel(this))
{
    hourLabel->setAlignment(Qt::AlignCenter);
    hourTempLabel->setAlignment(Qt::AlignCenter);
    hourWeatherIconLabel->setAlignment(Qt::AlignCenter);

    QFont font = hourTempLabel->font();
    font.setPointSize(18);
    font.setWeight(QFont::Bold);
    hourTempLabel->setFont(font);

    hourLayout->addWidget(hourWeatherIconLabel);
    hourLayout->addWidget(hourTempLabel);
    hourLayout->addWidget(hourLabel);

}

void DetailedWeatherPage::HourlyWeatherWidget::updateData(const int tempText, const int weatherCode,
                                                          const bool isDay, const QString timeStamp)
{
    hourLabel->setText(timeStamp);
    hourWeatherIcon->load(Settings::instance().weatherCodeToIcon(weatherCode, isDay));
    hourWeatherIconLabel->setPixmap(hourWeatherIcon->scaled(25, 25,
                                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
    hourTempLabel->setText(QString::number(tempText) + "°");
}


QString DetailedWeatherPage::getDaySuffix(const int day) {
    switch (day) {
    case 1: case 21: case 31:
        return "st";
    case 2: case 22:
        return "nd";
    case 3: case 23:
        return "rd";
    default:
        return "th";
    }
}

QString DetailedWeatherPage::weatherCodeToDescription(const int weatherCode) {
    switch (weatherCode) {
    case 0:
        return "Clear sky.";
    case 1:
        return "Partly cloudy skies.";
    case 2:
        return "Overcast skies.";
    case 3:
        return "Completely overcast.";
    case 45:
        return "Dense fog.";
    case 48:
        return "Freezing fog.";
    case 51:
    case 53:
    case 55:
        return "Moderate rain.";
    case 56:
    case 57:
        return "Freezing drizzle.";
    case 61:
        return "Moderate rain.";
    case 63:
        return "Heavy rainfall.";
    case 65:
        return "Heavy rain showers.";
    case 66:
    case 67:
        return "Icy rain.";
    case 71:
        return "Moderate snow.";
    case 73:
        return "Heavy snowfall.";
    case 75:
        return "Heavy snow showers.";
    case 77:
        return "Isolated snow showers.";
    case 80:
        return "Isolated rain showers.";
    case 81:
        return "Moderate rain showers.";
    case 82:
        return "Heavy rain showers.";
    case 85:
        return "Isolated snow showers.";
    case 86:
        return "Heavy snow showers.";
    case 95:
        return "Partly cloudy with thunder.";
    case 96:
    case 99:
        return "Partly cloudy with sleet, snow, and thunder.";
    default:
        return "Overcast skies.";
    }
}
