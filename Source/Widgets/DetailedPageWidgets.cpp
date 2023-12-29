#include "DetailedPageWidgets.h"

#include <QPainter>
#include <QStyleOption>
#include <QPainterPath>

#include "Settings.h"

namespace WidgetUtils{
QFrame* createLineFrame(QFrame::Shape shape, QString color = "white") {
    auto *line = new QFrame();
    line->setFrameShape(shape);
    line->setLineWidth(1);
    line->setStyleSheet("color: " + color + ";");
    return line;
}
}

BasicInfoWidget::BasicInfoWidget(QWidget *parent)
    : QWidget(parent)
    , basicInfoLayout(new QHBoxLayout())
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
    , dateTimeLayout(new QVBoxLayout())
    , iconLabel(new QLabel(this))
    , weatherDescriptionLabel(new QLabel(this))
    , todayLabel(new QLabel("Today,"))
    , dateLabel(new QLabel(this))
    , timeLabel(new QLabel(this))
    , temperatureLabel(new QLabel(this))
    , feelsLikeLabel(new QLabel(this))
{
    temperatureLabel->setStyleSheet("font-size: 110px; font-weight: bold;");
    leftLayout->addWidget(iconLabel, 0, Qt::AlignLeft);
    leftLayout->addWidget(weatherDescriptionLabel, 0, Qt::AlignLeft | Qt::AlignTop);

    dateTimeLayout->addWidget(dateLabel);
    dateTimeLayout->addWidget(timeLabel);
    dateTimeLayout->setSpacing(0);
    dateTimeLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addLayout(dateTimeLayout);

    rightLayout->addWidget(temperatureLabel, 0, Qt::AlignHCenter);
    rightLayout->addWidget(feelsLikeLabel, 0, Qt::AlignRight | Qt::AlignBottom);
    feelsLikeLabel->setStyleSheet(R"(
    QLabel {
        color: white;
        background-color: black;
        padding: 3px 8px;
        border-radius: 5px;
        font-size: 14px;
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

    QDateTime currentTime = QDateTime::currentDateTime().toTimeZone(timezone);
    dateLabel->setText("Today, " + currentTime.toString("MMMM d") + getDaySuffix(currentTime.date().day()));
    timeLabel->setText(currentTime.toString("HH:mm"));

    temperatureLabel->setText(QString::number(temperature) + "°");
        feelsLikeLabel->setText("Feels like: " + QString::number(apparentTemperature) + "°");
}

MinMaxTempWidget::MinMaxTempWidget(QWidget *parent)
    : QWidget{parent}
    , mainLayout(new QHBoxLayout(this))
{
        this->setObjectName("TempContainer");
        this->setStyleSheet("#TempContainer { "
                            "background-color: white;"
                            "border: 2px solid black;"
                            "border-radius: 15px; "
                            "margin: 5px; "
                            "}"
                            "#TempContainer QLabel { "
                            "color: black;"
                            "}"
                            );

        auto *maxTemp = new MinMaxTempWidgetItem("../Resources/temperature/uparrowBlack.png", "Highest temp:", this);
        auto *minTemp = new MinMaxTempWidgetItem("../Resources/temperature/downarrowBlack.png", "Lowest temp:", this);
        mainLayout->addWidget(maxTemp);
        mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine, "black"));
        mainLayout->addWidget(minTemp);

        this->setLayout(mainLayout);
}

void MinMaxTempWidget::updateData(const int maxTempValue, const int minTempValue)
{
        auto* maxWidget = static_cast<MinMaxTempWidgetItem*>(mainLayout->itemAt(0)->widget());
        maxWidget->updateData(maxTempValue, "°");
        auto* minWidget = static_cast<MinMaxTempWidgetItem*>(mainLayout->itemAt(2)->widget());
        minWidget->updateData(minTempValue, "°");
}

MinMaxTempWidget::MinMaxTempWidgetItem::MinMaxTempWidgetItem(const QString iconPath, const QString infoName, QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QHBoxLayout(this))
    , infoIcon(new QPixmap(iconPath))
    , infoIconLabel(new QLabel(this))
    , infoLabel(new QLabel(infoName))
    , info(new QLabel(this))
{
        infoIconLabel->setPixmap(infoIcon->scaled(iconWidth, iconHeight,
                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mainLayout->addWidget(infoIconLabel);
        mainLayout->addWidget(infoLabel);
        mainLayout->addWidget(info);
        mainLayout->addStretch(1);

        this->setLayout(mainLayout);
}

void MinMaxTempWidget::MinMaxTempWidgetItem::updateData(const int value, const QString unit)
{
        info->setText(QString::number(value) + unit);
}


SunWidget::SunWidget(QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QHBoxLayout(this))
{
        this->setObjectName("SunContainer");
        this->setStyleSheet("#SunContainer { "
                            "background-color: black;"
                            "border-radius: 15px; "
                            "margin: 5px; "
                            "}"
                            "#SunContainer QLabel { "
                            "color: white;"
                            "}"
                            );

        auto *sunrise = new SunWidgetItem("../Resources/sunrise+sunset/sunrise.png", "Sunrise", this);
        auto *sunset = new SunWidgetItem("../Resources/sunrise+sunset/sunset.png", "Sunset", this);
        mainLayout->addWidget(sunrise);
        mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
        mainLayout->addWidget(sunset);

        this->setLayout(mainLayout);
}

void SunWidget::updateData(const QTimeZone &timezone, const QVector<QString> sunriseValues, const QVector<QString> sunsetValues)
{
        auto* sunriseWidget = static_cast<SunWidgetItem*>(mainLayout->itemAt(0)->widget());
        sunriseWidget->updateData(timezone, sunriseValues);
        auto* sunsetWidget = static_cast<SunWidgetItem*>(mainLayout->itemAt(2)->widget());
        sunsetWidget->updateData(timezone, sunsetValues);
}

SunWidget::SunWidgetItem::SunWidgetItem(const QString iconPath, const QString infoName, QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QHBoxLayout(this))
    , timeLayout(new QVBoxLayout())
    , infoIcon(new QPixmap(iconPath))
    , infoIconLabel(new QLabel(this))
    , infoLabel(new QLabel(infoName))
    , info(new QLabel(this))
    , additionalinfo(new QLabel(this))
{
        mainLayout->addWidget(infoLabel);
        infoIconLabel->setPixmap(infoIcon->scaled(iconWidth, iconHeight,
                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mainLayout->addStretch(1);
        mainLayout->addWidget(infoIconLabel);
        mainLayout->addStretch(1);

        additionalinfo->setStyleSheet("font-size: 18px;");
        additionalinfo->setStyleSheet("font-size: 12px; color: gray;");
        timeLayout->addWidget(info);
        timeLayout->addWidget(additionalinfo);
        mainLayout->addLayout(timeLayout);

        this->setLayout(mainLayout);
}

void SunWidget::SunWidgetItem::updateData(const QTimeZone &timezone, const QVector<QString> values)
{
        info->setText(values[0].mid(11,5));

        QDateTime specifiedTime = QDateTime::fromString(values[0], Qt::ISODate);
        specifiedTime.setTimeZone(timezone);
        QDateTime currentTime = QDateTime::currentDateTime().toTimeZone(timezone);

        if(specifiedTime < currentTime){
            specifiedTime = QDateTime::fromString(values[1], Qt::ISODate);
            specifiedTime.setTimeZone(timezone);
        }
        auto differenceInSeconds = currentTime.secsTo(specifiedTime);
        int hours = differenceInSeconds / 3600;
        int minutes = (differenceInSeconds % 3600) / 60;

        additionalinfo->setText("+" + QString::number(hours) + "h " +
                                QString::number(minutes) + "m");
}

HumidityUvRainWidget::HumidityUvRainWidget(QWidget *parent)
    : QWidget{parent}
    , mainLayout(new QHBoxLayout(this))
    , humidity(new singleWidgetItem("../Resources/humidity/humidity.png", "Humidity", this))
    , uvIndex(new singleWidgetItem("../Resources/uv/uv.png", "UV Index", this))
    , rain(new singleWidgetItem("../Resources/precipitation/raindrop.png", "Precipitation", this))
{
    this->setObjectName("HumidityUvRainContainer");
    this->setStyleSheet("#HumidityUvRainContainer { "
                        "background-color: black;"
                        "border-radius: 15px; "
                        "margin: 5px; "
                        "}"
                        "#HumidityUvRainContainer QLabel { "
                        "color: white;"
                        "}");
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
    , snow(new singleWidgetItem("../Resources/snow/snowflake.png", "Snow depth", this))
{
    this->setObjectName("VisibilityPressureSnowContainer");
    this->setStyleSheet("#VisibilityPressureSnowContainer { "
                        "background-color: black;"
                        "border-radius: 15px; "
                        "margin: 5px; "
                        "}"
                        "#VisibilityPressureSnowContainer QLabel { "
                        "color: white;"
                        "}");
    mainLayout->addWidget(visibility);
    mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
    mainLayout->addWidget(pressure);
    mainLayout->addWidget(WidgetUtils::createLineFrame(QFrame::VLine));
    mainLayout->addWidget(snow);

    this->setLayout(mainLayout);
}

void VisibilityPressureSnowWidget::updateData(const int visibilityValue, const int pressureValue, double snowValue)
{
    visibility->updateData(visibilityValue, " " + Settings::instance().visibilityUnitString());
    pressure->updateData(pressureValue, " hPa");

    if(Settings::instance().precipitationUnitApiParameter() == "mm"){
        snow->updateData(static_cast<int>(qRound(snowValue * 100)), " m");
    }
    else
        snow->updateData(static_cast<int>(qRound(snowValue * 12)), " in");
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
    windSpeedLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    windSpeed->setAlignment(Qt::AlignLeft);
    leftLayout->addWidget(windSpeedLabel);
    leftLayout->addWidget(windSpeed);

    windGustsLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
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
        auto* widget = static_cast<HourlyWidgetItem*>(itemsLayout->itemAt(i)->widget());
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
        mainLayout->addWidget(widget, i, 0);
    }
    this->setLayout(mainLayout);
}

void DailyWeatherWidget::updateData(const QVector<QString> &dayNames, const QVector<int> &weatherCodes,
                                    const QVector<int> &minTemps, const QVector<int> &maxTemps)
{
    for (int i = 0; i < daysPerWeek; ++i) {
        auto* widget = static_cast<DailyWidgetItem*>(mainLayout->itemAt(i)->widget());
        widget->updateData(dayNames[i], weatherCodes[i], minTemps[i], maxTemps[i]);
    }
}

DailyWeatherWidget::DailyWidgetItem::DailyWidgetItem(QWidget *parent)
    : QWidget(parent)
    , dailyLayout(new QHBoxLayout(this))
    , dayNameLabel(new QLabel())
    , dayWeatherIconLabel(new QLabel(this))
    , dailyminTempLabel(new QLabel(this))
    , temperatureIcon(QPixmap("../Resources/temperature/temperatureBlack.png"))
    , temperatureIconLabel(new QLabel())
    , dailymaxTempLabel(new QLabel(this))
{
    this->setObjectName("DailyWeatherItemContainer");
    this->setStyleSheet("#DailyWeatherItemContainer { "
                        "border-radius: " + QString::number(border) + "px; "
                        "margin: 5px; "
                        "}"
                        "#DailyWeatherItemContainer QLabel { "
                        "color: black;"
                        "}");

    dayNameLabel->setFixedWidth(dayNameLabelWidth);
    dayNameLabel->setContentsMargins(padding, 0, 0, 0);
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

    dailymaxTempLabel->setFixedWidth(dailyMaxLabelWidth);
    dailymaxTempLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    dailyLayout->addWidget(dailymaxTempLabel);

    setAutoFillBackground(true);
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

void DailyWeatherWidget::DailyWidgetItem::paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);

        QPainter painter(this);
        QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
        gradient.setColorAt(0, QColor("#a2a2a2"));
        gradient.setColorAt(1, QColor("#ffffff"));

        QBrush brush(gradient);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);

        QStyleOption opt;
        opt.initFrom(this);

        QPainterPath path;
        path.addRoundedRect(rect(), border, border);
        painter.setClipPath(path);
        painter.fillPath(path, brush);
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
