#include "DetailedPageWidgets.h"

#include "Settings.h"

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
            auto *line = new QFrame();
            line->setFrameShape(QFrame::HLine);
            line->setLineWidth(1);
            line->setStyleSheet("color: black;");
            mainLayout->addWidget(line, 2*i + 1, 0, 1, -1);
        }
    }
}

void DailyWeatherWidget::updateData(const QVector<QString> &dayNames, const QVector<int> &weatherCodes,
                                    const QVector<int> &minTemps, const QVector<int> &maxTemps)
{
    //todo magic number
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
