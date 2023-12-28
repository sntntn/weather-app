#include "DetailedPageWidgets.h"

#include <QPainter>

#include "Settings.h"

namespace WidgetUtils{
    QFrame* createLineFrame(QFrame::Shape shape) {
        auto *line = new QFrame();
        line->setFrameShape(shape);
        line->setLineWidth(1);
        line->setStyleSheet("color: black;");
        return line;
    }
}

BasicInfoWidget::BasicInfoWidget(QWidget *parent)
    : QWidget(parent)
    , basicInfoLayout(new QHBoxLayout())
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
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

void BasicInfoWidget::updateData(const int weatherCode, const bool isDay,
                                 const QTimeZone &timezone, const int temperature,
                                 const int apparentTemperature)
{
    weatherIcon.load(Settings::instance().weatherCodeToIcon(weatherCode, isDay));
    iconLabel->setPixmap(weatherIcon.scaled(iconWidth, iconHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedHeight(iconHeight);

    weatherDescriptionLabel->setText(weatherCodeToDescription(weatherCode));

    QDateTime currentTimeZone = QDateTime::currentDateTime().toTimeZone(timezone);
    dateLabel->setText(currentTimeZone.toString("'Today,' MMMM d") +
                       getDaySuffix(currentTimeZone.date().day()));
    timeLabel->setText(currentTimeZone.toString("HH:mm"));

    temperatureLabel->setText(QString::number(temperature) + "°");
        feelsLikeLabel->setText("Feels like: " + QString::number(apparentTemperature) + "°");
}

HumidityUvRainWidget::HumidityUvRainWidget(QWidget *parent)
    : QWidget{parent}
    , mainLayout(new QHBoxLayout(this))
    , humidity(new singleWidgetItem("../Resources/humidity/humidity.png", "Humidity", this))
    , uvIndex(new singleWidgetItem("../Resources/uv/uv.png", "UV Index", this))
    , rain(new singleWidgetItem("../Resources/precipitation/raindrop.png", "Rain", this))
{
    mainLayout->addWidget(humidity);
    mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
    mainLayout->addWidget(uvIndex);
    mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
    mainLayout->addWidget(rain);

    this->setLayout(mainLayout);
}

void HumidityUvRainWidget::updateData(const int humidityValue, const int uvIndexValue, const int rainValue)
{
    humidity->updateData(humidityValue, "%");
    uvIndex->updateData(uvIndexValue, " (" + uvIndextoDescription(uvIndexValue) + ")");
    rain->updateData(rainValue, " " + Settings::instance().precipitationUnitString());
}

VisibilityPressureSnowWidget::VisibilityPressureSnowWidget(QWidget *parent)
    : QWidget{parent}
    , mainLayout(new QHBoxLayout(this))
    , visibility(new singleWidgetItem("../Resources/visibility/visibility.png", "Visibility", this))
    , pressure(new singleWidgetItem("../Resources/pressure/pressure1.png", "Pressure", this))
    , snow(new singleWidgetItem("../Resources/snow/snowflake.png", "Snow", this))
{
    mainLayout->addWidget(visibility);
    mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
    mainLayout->addWidget(pressure);
    mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
    mainLayout->addWidget(snow);

    this->setLayout(mainLayout);
}

void VisibilityPressureSnowWidget::updateData(const int visibilityValue, const int pressureValue, const int snowValue)
{
    visibility->updateData(visibilityValue, " " + Settings::instance().visibilityUnitString());
    pressure->updateData(pressureValue, "hPa");
    snow->updateData(snowValue, " " + Settings::instance().precipitationUnitString());
}

WindInfoWidget::WindInfoWidget(QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QHBoxLayout(this))
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
    , windGustsLabel(new QLabel("Wind Gusts"))
    , windGusts(new QLabel())
    , windSpeedLabel(new QLabel("Wind Speed"))
    , windSpeed(new QLabel())
    , compassLabel(new QLabel(this))
    , initialCompassIcon(QPixmap("../Resources/wind/whiteCompass.png"))
    , arrowIcon(QPixmap("../Resources/wind/whiteArrow.png"))
{
    windSpeedLabel->setAlignment(Qt::AlignLeft);
    windSpeed->setAlignment(Qt::AlignLeft);
    leftLayout->addWidget(windSpeedLabel);
    leftLayout->addWidget(windSpeed);

    windGustsLabel->setAlignment(Qt::AlignRight);
    windGusts->setAlignment(Qt::AlignRight);
    rightLayout->addWidget(windGustsLabel);
    rightLayout->addWidget(windGusts);

    mainLayout->addLayout(leftLayout);
    compassLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(compassLabel);
    mainLayout->addLayout(rightLayout);
    this->setLayout(mainLayout);
}

void WindInfoWidget::updateData(const int windSpeedValue, const int windGustsValue, const int windDirectionValue)
{

    windSpeed->setText(QString::number(windSpeedValue) + Settings::instance().windSpeedUnitString());
    windGusts->setText(QString::number(windGustsValue) + Settings::instance().windSpeedUnitString());

    QPixmap compassIcon = initialCompassIcon.copy();
    QPainter painter(&compassIcon);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPoint center(compassIcon.width() / 2, compassIcon.height() / 2);

    painter.translate(center);
    painter.rotate(windDirectionValue - 180);
    painter.translate(-center);

    painter.drawPixmap(center.x() - arrowIcon.width() / 2,
                       center.y() - arrowIcon.height() / 2,
                       arrowIcon);
    painter.end();

    compassLabel->setPixmap(compassIcon.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

SunriseSunsetWidget::SunriseSunsetWidget(QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QHBoxLayout(this))
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
    , sunriseLabel(new QLabel("Sunrise"))
    , sunsetLabel(new QLabel("Sunset"))
    , sunriseIconLabel(new QLabel())
    , sunsetIconLabel(new QLabel())
    , sunriseIcon(QPixmap("../Resources/sunrise+sunset/sunrise.png"))
    , sunsetIcon(QPixmap("../Resources/sunrise+sunset/sunset.png"))
    , sunriseTime(new QLabel())
    , sunsetTime(new QLabel())
{
    sunriseLabel->setAlignment(Qt::AlignLeft);
    sunriseIconLabel->setAlignment(Qt::AlignLeft);
    sunriseTime->setAlignment(Qt::AlignLeft);
    leftLayout->addWidget(sunriseLabel);
    leftLayout->addWidget(sunriseIconLabel);
    leftLayout->addWidget(sunriseTime);

    sunsetLabel->setAlignment(Qt::AlignRight);
    sunsetIconLabel->setAlignment(Qt::AlignRight);
    sunsetTime->setAlignment(Qt::AlignRight);
    rightLayout->addWidget(sunsetLabel);
    rightLayout->addWidget(sunsetIconLabel);
    rightLayout->addWidget(sunsetTime);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    this->setLayout(mainLayout);
}

void SunriseSunsetWidget::updateData(const QString sunrise, const QString sunset)
{
    sunriseTime->setText(sunrise);
    sunsetTime->setText(sunset);

    QPixmap sunrisePic = sunriseIcon.copy();
    QPixmap sunsetPic = sunsetIcon.copy();

    //hourWeatherIcon.load(Settings::instance().weatherCodeToIcon(weatherCode, isDay));
    //hourWeatherIconLabel->setPixmap(hourWeatherIcon.scaled(iconWidth, iconHeight,
    //                                                       Qt::KeepAspectRatio, Qt::SmoothTransformation));

//    QPainter sunrisePainter(&sunrisePic);
//    QPainter sunsetPainter(&sunsetPic);
//
//    sunrisePainter.setRenderHint(QPainter::Antialiasing);
//    sunrisePainter.setRenderHint(QPainter::SmoothPixmapTransform);
//
//    sunsetPainter.setRenderHint(QPainter::Antialiasing);
//    sunsetPainter.setRenderHint(QPainter::SmoothPixmapTransform);
//
//    QPoint center(sunrisePic.width() / 2, sunrisePic.height() / 2);
//
//    sunrisePainter.translate(center);
//    sunrisePainter.end();

    sunriseIconLabel->setPixmap(sunrisePic.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sunsetIconLabel->setPixmap(sunsetPic.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

};

singleWidgetItem::singleWidgetItem(const QString iconPath, const QString infoName, QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QVBoxLayout(this))
    , lowerLayout(new QHBoxLayout())
    , infoIcon(new QPixmap(iconPath))
    , infoIconLabel(new QLabel(this))
    , infoLabel(new QLabel(infoName))
    , info(new QLabel(this))
{
    mainLayout->addWidget(infoLabel);
    infoIconLabel->setPixmap(infoIcon->scaled(iconWidth, iconHeight,
                                              Qt::KeepAspectRatio, Qt::SmoothTransformation));
    lowerLayout->addWidget(infoIconLabel);
    lowerLayout->addWidget(info);
    mainLayout->addLayout(lowerLayout);

    this->setLayout(mainLayout);
}

void singleWidgetItem::updateData(const int value, const QString unit)
{
    info->setText(QString::number(value) + unit);
}

HourlyWeatherWidget::HourlyWeatherWidget(QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QVBoxLayout(this))
    , hourlyWeatherArea(new QScrollArea(this))
    , hourlyWeatherContents(new QWidget(this))
    , itemsLayout(new QHBoxLayout())
{
    for(int i = 0; i < hoursPerDay; i++){
        auto *widget = new HourlyWidgetItem(this);
        widget->setFixedSize(widgetItemWidth, widgetItemHeight);
        itemsLayout->addWidget(widget);
    }

    hourlyWeatherContents->setLayout(itemsLayout);
    hourlyWeatherArea->setWidget(hourlyWeatherContents);
    hourlyWeatherArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hourlyWeatherArea->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    mainLayout->addWidget(hourlyWeatherArea);
    this->setLayout(mainLayout);
}

void HourlyWeatherWidget::updateData(const QVector<int> &temperatures, const QVector<int> &weatherCodes,
                                     const QVector<bool> &isDays, const QVector<QString> &timeStamps)
{
    for (int i = 0; i < hoursPerDay; ++i) {
        QLayoutItem* item = itemsLayout->itemAt(i);
        auto* widget = static_cast<HourlyWidgetItem*>(item->widget());
        widget->updateData(temperatures[i], weatherCodes[i],
                           isDays[i], timeStamps[i]);
    }
}

HourlyWeatherWidget::HourlyWidgetItem::HourlyWidgetItem(QWidget *parent)
    : QWidget(parent)
    , hourLayout(new QVBoxLayout(this))
    , hourLabel(new QLabel())
    , hourWeatherIconLabel(new QLabel(this))
    , hourTempLabel(new QLabel(this))
{
    hourLabel->setAlignment(Qt::AlignCenter);
    hourTempLabel->setAlignment(Qt::AlignCenter);
    hourWeatherIconLabel->setAlignment(Qt::AlignCenter);

    hourTempLabel->setStyleSheet("font: bold 18px;");

    hourLayout->addWidget(hourWeatherIconLabel);
    hourLayout->addWidget(hourTempLabel);
    hourLayout->addWidget(hourLabel);
}

void HourlyWeatherWidget::HourlyWidgetItem::updateData(const int tempText, const int weatherCode,
                                                       const bool isDay, const QString &timeStamp)
{
    hourLabel->setText(timeStamp);
    hourWeatherIcon.load(Settings::instance().weatherCodeToIcon(weatherCode, isDay));
    hourWeatherIconLabel->setPixmap(hourWeatherIcon.scaled(iconWidth, iconHeight,
                                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
    hourTempLabel->setText(QString::number(tempText) + "°");
}

DailyWeatherWidget::DailyWeatherWidget(QWidget *parent)
    : QWidget{parent}
    , mainLayout(new QGridLayout(this))
{
    for(int i = 0; i < daysPerWeek; i++){
        auto *widget = new DailyWidgetItem(this);
        mainLayout->addWidget(widget, 2*i, 0);

        if (i < 6) {
            mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::HLine), 2*i + 1, 0, 1, -1);
        }
    }
}

void DailyWeatherWidget::updateData(const QVector<QString> &dayNames, const QVector<int> &weatherCodes,
                                    const QVector<int> &minTemps, const QVector<int> &maxTemps)
{
    for (int i = 0; i < daysPerWeek; ++i) {
        QLayoutItem* item = mainLayout->itemAt(2*i);
        auto* widget = static_cast<DailyWidgetItem*>(item->widget());
        widget->updateData(dayNames[i], weatherCodes[i], minTemps[i], maxTemps[i]);
    }
}

DailyWeatherWidget::DailyWidgetItem::DailyWidgetItem(QWidget *parent)
    : QWidget(parent)
    , dailyLayout(new QHBoxLayout(this))
    , dayNameLabel(new QLabel())
    , dayWeatherIconLabel(new QLabel(this))
    , dailyminTempLabel(new QLabel(this))
    , temperatureIcon(QPixmap("../Resources/temperature/temperature.png"))
    , temperatureIconLabel(new QLabel())
    , dailymaxTempLabel(new QLabel(this))
{
    dayNameLabel->setFixedWidth(dayNameLabelWidth);
    dailyLayout->addWidget(dayNameLabel);
    dailyLayout->addStretch(1);

    dayWeatherIconLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dayWeatherIconLabel);
    dailyLayout->addStretch(1);

    dailyminTempLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dailyminTempLabel);

    temperatureIconLabel->setPixmap(temperatureIcon.scaled(iconWidth, iconHeight,
                                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
    dailyLayout->addWidget(temperatureIconLabel);

    dailymaxTempLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dailymaxTempLabel);
}

void DailyWeatherWidget::DailyWidgetItem::updateData(const QString &dayName, const int weatherCode,
                                                         const int minTemp, const int maxTemp)
{
    dayNameLabel->setText(dayName);
    dayWeatherIcon.load(Settings::instance().weatherCodeToIcon(weatherCode, true));
    dayWeatherIconLabel->setPixmap(dayWeatherIcon.scaled(iconWidth, iconHeight,
                                                          Qt::KeepAspectRatio, Qt::SmoothTransformation));
    dailyminTempLabel->setText(QString::number(minTemp) + "°");
    dailymaxTempLabel->setText(QString::number(maxTemp) + "°");
}

QString HumidityUvRainWidget::uvIndextoDescription(const int uvIndex)
{
    switch(uvIndex){
    case 0:
    case 1:
    case 2:
        return "Safe";
    case 3:
    case 4:
    case 5:
        return "Low risk";
    case 6:
    case 7:
        return "Moderate risk";
    case 8:
    case 9:
    case 10:
        return "High risk";
    default:
        return "Dangerous";
    }
}

QString BasicInfoWidget::getDaySuffix(const int day) {
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

QString BasicInfoWidget::weatherCodeToDescription(const int weatherCode) {
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
