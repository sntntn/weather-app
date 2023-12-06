#include "WeatherWidget.h"

#include <QString>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QFont>
#include <QPalette>
#include <QFrame>

#include "WeatherData.h"

WeatherWidget::WeatherWidget(const QSharedPointer<WeatherData> &data, QWidget *parent)
    : QWidget{parent}
    , data(data)
    , hBox(new QHBoxLayout(this))
    , leftVBox(new QVBoxLayout())
    , rightVBox(new QVBoxLayout())
    , locationLabel(new QLabel(data->location.getRenamedPlace(), this))
    , temperatureLabel(new QLabel(QString::number(data->temperature), this))
    , minmaxTemperatureLabel(new QLabel("H:" + QString::number(data->highestTemperature) + " L:" + QString::number(data->lowestTemperature), this))
    , timeLabel(new QLabel(QDateTime::currentDateTime().toTimeZone(data->timezone).toString("HH:mm"), this))
    , iconLabel(new QLabel(this))
    , weatherIcon(weatherCodeToIcon(data->weatherCode, data->isDay))
{
    hBox->setSpacing(5);
    hBox->setContentsMargins(10, 10, 10, 10);
    hBox->addLayout(leftVBox);
    hBox->addLayout(rightVBox);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("WeatherWidget { border-radius: 20px; background-color: #598be0; }");

    locationLabel->setFont(QFont("Arial", 18, QFont::Bold));
    timeLabel->setFont(QFont("Arial", 14, QFont::Normal));
    temperatureLabel->setFont(QFont("Arial", 24, QFont::Bold));
    minmaxTemperatureLabel->setFont(QFont("Arial", 14, QFont::Normal));
    iconLabel->setPixmap(weatherIcon.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedSize(50,50);

    QString labelStyle = "QLabel { color: white; }";
    locationLabel->setStyleSheet(labelStyle);
    timeLabel->setStyleSheet(labelStyle);
    temperatureLabel->setStyleSheet(labelStyle);

    //TODO
    auto* hLayout = new QHBoxLayout();
    //QSpacerItem* spacer = new QSpacerItem();
    hLayout->addStretch();
    hLayout->addWidget(temperatureLabel);
    //hLayout->addWidget(iconLabel);

    leftVBox->addWidget(locationLabel);
    leftVBox->addWidget(timeLabel);
    rightVBox->addWidget(iconLabel, 0, Qt::AlignTop | Qt::AlignRight);
    //rightVBox->addWidget(temperatureLabel, 0, Qt::AlignTop | Qt::AlignRight);
    rightVBox->addLayout(hLayout);
    rightVBox->addWidget(minmaxTemperatureLabel, 0, Qt::AlignBottom | Qt::AlignRight);

    setLayout(hBox);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

}

void WeatherWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked(data->location);
}

QString WeatherWidget::weatherCodeToIcon(int weatherCode, bool isDay) {
    QString iconBasePath = "../Resources/weatherIcons/";

    switch (weatherCode) {
    case 0:
        return isDay ? iconBasePath + "Sunny.png" : iconBasePath + "Clear.png";
    case 1:
        return isDay ? iconBasePath + "PartlyCloudyDay.png" : iconBasePath + "PartlyCloudyNight.png";
    case 2:
        return iconBasePath + "Cloudy.png";
    case 3:
        return iconBasePath + "Overcast.png";
    case 45:
        return iconBasePath + "Fog.png";
    case 48:
        return iconBasePath + "FreezingFog.png";
    case 51:
    case 53:
    case 55:
        return iconBasePath + "ModRain.png";
    case 56:
    case 57:
        return iconBasePath + "FreezingDrizzle.png";
    case 61:
        return iconBasePath + "ModRain.png";
    case 63:
        return iconBasePath + "HeavyRain.png";
    case 65:
        return isDay ? iconBasePath + "HeavyRainSwrsDay.png" : iconBasePath + "HeavyRainSwrsNight.png";
    case 66:
    case 67:
        return iconBasePath + "FreezingRain.png";
    case 71:
        return iconBasePath + "ModSnow.png";
    case 73:
        return iconBasePath + "HeavySnow.png";
    case 75:
        return isDay ? iconBasePath + "HeavySnowSwrsDay.png" : iconBasePath + "HeavySnowSwrsNight.png";
    case 77:
        return isDay ? iconBasePath + "IsoSnowSwrsDay.png" : iconBasePath + "IsoSnowSwrsNight.png";
    case 80:
        return isDay ? iconBasePath + "IsoRainSwrsDay.png" : iconBasePath + "IsoRainSwrsNight.png";
    case 81:
        return isDay ? iconBasePath + "ModRainSwrsDay.png" : iconBasePath + "ModRainSwrsNight.png";
    case 82:
        return isDay ? iconBasePath + "HeavyRainSwrsDay.png" : iconBasePath + "HeavyRainSwrsNight.png";
    case 85:
        return isDay ? iconBasePath + "IsoSnowSwrsDay.png" : iconBasePath + "IsoSnowSwrsNight.png";
    case 86:
        return isDay ? iconBasePath + "HeavySnowSwrsDay.png" : iconBasePath + "HeavySnowSwrsNight.png";
    case 95:
        return isDay ? iconBasePath + "PartCloudRainThunderDay.png" : iconBasePath + "PartCloudRainThunderNight.png";
    case 96:
    case 99:
        return isDay ? iconBasePath + "PartCloudSleetSnowThunderDay.png" : iconBasePath + "PartCloudSleetSnowThunderNight.png";
    default:
        return iconBasePath + "Cloudy.png"; // Default case if no code matches
    }
}


