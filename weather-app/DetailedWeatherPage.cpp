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
#include <QFrame>

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
    , basicInfo(new BasicInfoWidget(this))
    , minmaxTemperature(new QLabel(this))
    , compassLabel(new QLabel(this))
    , initialCompassIcon(new QPixmap("../Resources/wind/whiteCompass.png"))
    , arrowIcon(new QPixmap("../Resources/wind/whiteArrow.png"))
    , hourly(new QLabel("Hourly"))
    , hourlyWidget(new HourlyWeatherWidget(this))
    , daily(new QLabel("7-DAY FORECAST"))
    , dailyWidget(new DailyWeatherWidget(this))
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

//    for(int i = 0; i < 7; i++){
//        DailyWeatherWidget *widget = new DailyWeatherWidget(this);
//        dailyLayout->addWidget(widget, 2*i, 0);

//        if (i < 6) {
//            QFrame *line = new QFrame();
//            line->setFrameShape(QFrame::HLine);
//            line->setLineWidth(1);
//            line->setStyleSheet("color: black;");
//            dailyLayout->addWidget(line, 2*i + 1, 0, 1, -1);
//        }
//    }

    locationLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    weatherLayout->addWidget(locationLabel, 0, Qt::AlignHCenter);
    weatherLayout->addWidget(basicInfo);
    basicInfo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    minmaxTemperature->setStyleSheet("font-size: 16px;");
    weatherLayout->addWidget(minmaxTemperature, 0, Qt::AlignHCenter);

//    daily->setStyleSheet("font: bold 15px; margin: 10px;");
//    daily->setAlignment(Qt::AlignHCenter);
//    weatherLayout->addWidget(daily);
//    weatherLayout->addLayout(dailyLayout);

    hourly->setStyleSheet("font: bold 15px;");
    weatherLayout->addWidget(hourly);
    weatherLayout->addWidget(hourlyWidget);
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
    //todo izbrisi SharedPointer
    QSharedPointer<DetailedWeatherData> detailedData = qSharedPointerCast<DetailedWeatherData>(data);
    this->data = detailedData;
    highlightWidget();

    locationLabel->setText(detailedData->location().getRenamedPlace());
    //todo (need country from api)countryLabel->setText(detailedData->location.get)

    basicInfo->updateData(this->data->weatherCode(), this->data->isDay(), this->data->timezone(),
                          this->data->temperature(), this->data->apparentTemperature());

    minmaxTemperature->setText("H:" + QString::number(detailedData->weeklyMaxTemp()[0]) + "°  L:"
                               + QString::number(detailedData->weeklyMinTemp()[0]) + "°");

    hourlyWidget->updateData(this->data->hourlyTemperature(), this->data->hourlyCode(),
                             this->data->hourlyIsDay(), this->data->hourlyTimeStamp());

    //todo magic number
    for (int i = 0; i < 7; ++i) {
        QLayoutItem* item = dailyLayout->itemAt(2*i);
        DailyWeatherWidget* widget = dynamic_cast<DailyWeatherWidget*>(item->widget());
        widget->updateData(this->data->weeklyDayName()[i], this->data->weeklyCode()[i],
                           this->data->weeklyMinTemp()[i], this->data->weeklyMaxTemp()[i]);
    }

    QPixmap compassIcon = initialCompassIcon->copy();
    QPainter painter(&compassIcon);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPoint center(compassIcon.width() / 2, compassIcon.height() / 2);

    painter.translate(center);
    painter.rotate(detailedData->windDirection() - 180);
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
    Settings::instance().savedLocations().push_back(this->data->location());
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
        return widget->data->location() == this->data->location();
    });

    if (newSelectedWidget != m_widgets.end()) {
        selectedWidget = *newSelectedWidget;
        widgetsScrollArea->ensureWidgetVisible(selectedWidget);
        selectedWidget->setHighlight();
    }
}

DetailedWeatherPage::BasicInfoWidget::BasicInfoWidget(QWidget *parent)
    : QWidget(parent)
    , basicInfoLayout(new QHBoxLayout())
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
    , weatherIcon(new QPixmap())
    , iconLabel(new QLabel(this))
    , weatherDescriptionLabel(new QLabel(this))
    , dateLabel(new QLabel(this))
    , timeLabel(new QLabel(this))
    , temperatureLabel(new QLabel(this))
    , feelsLikeLabel(new QLabel(this))
{
    temperatureLabel->setStyleSheet("font-size: 110px; font-weight: bold;");
    leftLayout->addWidget(iconLabel, 0, Qt::AlignLeft);
    leftLayout->addWidget(weatherDescriptionLabel, 0, Qt::AlignLeft);
    leftLayout->addWidget(dateLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    leftLayout->addWidget(timeLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    rightLayout->addWidget(temperatureLabel, 0, Qt::AlignHCenter);
    rightLayout->addWidget(feelsLikeLabel, 0, Qt::AlignRight | Qt::AlignBottom);
    feelsLikeLabel->setStyleSheet(R"(
    QLabel {
        color: white;
        background-color: #0066CC;
        padding: 3px 5px;
        border-radius: 5px;
        font-size: 14px;
        font-weight: bold;
    }
    )");
    basicInfoLayout->addLayout(leftLayout);
    basicInfoLayout->addLayout(rightLayout);
    this->setLayout(basicInfoLayout);
}

void DetailedWeatherPage::BasicInfoWidget::updateData(const int weatherCode, const bool isDay,
                                                      const QTimeZone timezone, const int temperature,
                                                      const int apparentTemperature)
{
    weatherIcon->load(Settings::instance().weatherCodeToIcon(weatherCode, isDay));
    iconLabel->setPixmap(weatherIcon->scaled(iconWidth, iconHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedHeight(iconHeight);

    weatherDescriptionLabel->setText(weatherCodeToDescription(weatherCode));

    QDateTime currentTimeZone = QDateTime::currentDateTime().toTimeZone(timezone);
    dateLabel->setText(currentTimeZone.toString("'Today,' MMMM d") +
                       getDaySuffix(currentTimeZone.date().day()));
    timeLabel->setText(currentTimeZone.toString("HH:mm"));

    temperatureLabel->setText(QString::number(temperature) + "°");
    feelsLikeLabel->setText("Feels like: " + QString::number(apparentTemperature) + "°");
}

DetailedWeatherPage::DailyWeatherWidget::DailyWeatherWidget(QWidget *parent)
    : QWidget(parent)
    , dailyLayout(new QHBoxLayout(this))
    , dayNameLabel(new QLabel())
    , dayWeatherIcon(new QPixmap())
    , dayWeatherIconLabel(new QLabel(this))
    , dailyminTempLabel(new QLabel(this))
    , temperatureIcon(new QPixmap("../Resources/temperature/temperature.png"))
    , temperatureIconLabel(new QLabel())
    , dailymaxTempLabel(new QLabel(this))
{
    dayNameLabel->setFixedWidth(80);
    dailyLayout->addWidget(dayNameLabel);
    dailyLayout->addStretch(1);

    dayWeatherIconLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dayWeatherIconLabel);
    dailyLayout->addStretch(1);

    dailyminTempLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dailyminTempLabel);

    temperatureIconLabel->setPixmap(temperatureIcon->scaled(25, 25,
                                                           Qt::KeepAspectRatio, Qt::SmoothTransformation));
    dailyLayout->addWidget(temperatureIconLabel);

    dailymaxTempLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dailymaxTempLabel);
}

void DetailedWeatherPage::DailyWeatherWidget::updateData(const QString dayName, const int weatherCode, const int minTemp, const int maxTemp)
{
    dayNameLabel->setText(dayName);
    //todo True for isDay
    dayWeatherIcon->load(Settings::instance().weatherCodeToIcon(weatherCode, 1));
    dayWeatherIconLabel->setPixmap(dayWeatherIcon->scaled(30, 30,
                                                           Qt::KeepAspectRatio, Qt::SmoothTransformation));
    dailyminTempLabel->setText(QString::number(minTemp) + "°");
    dailymaxTempLabel->setText(QString::number(maxTemp) + "°");
}

QString DetailedWeatherPage::BasicInfoWidget::getDaySuffix(const int day) {
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

QString DetailedWeatherPage::BasicInfoWidget::weatherCodeToDescription(const int weatherCode) {
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
