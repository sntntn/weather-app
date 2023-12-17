#include "WeatherWidget.h"

#include <QString>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QFont>
#include <QPalette>
#include <QFrame>
#include <QMargins>
#include <QLineEdit>

#include "WeatherData.h"
#include "Settings.h"

WeatherWidget::WeatherWidget(const QSharedPointer<WeatherData> &data, QWidget *parent)
    : QWidget{parent}
    , data(data)
    , mainLayout(new QHBoxLayout(this))
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
    , temperatureLabel(new QLabel(QString::number(data->temperature()) + "°", this))
    , locationLabel(new QLabel(data->location().getRenamedPlace().toUpper(), this))
    , maxTemperatureLabel(new QLabel("H:" + QString::number(data->highestTemperature()) + "°", this))
    , minTemperatureLabel(new QLabel("L:" + QString::number(data->lowestTemperature()) + "°", this))
    , timeLabel(new QLabel(QDateTime::currentDateTime().toTimeZone(data->timezone()).toString("HH:mm"), this))
    , iconLabel(new QLabel(this))
    , weatherIcon(weatherCodeToIcon(data->weatherCode(), data->isDay()))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("WeatherWidget { border-radius: 20px; background-color: #598be0; }");

    mainLayout->setSpacing(hBoxSpacing);
    mainLayout->setContentsMargins(hBoxMarginSize, hBoxMarginSize, hBoxMarginSize, hBoxMarginSize);

    const QString fontName = "Roboto";
    locationLabel->setFont(QFont(fontName, adjustLabelFontSize(fontName), QFont::Bold));
    timeLabel->setFont(QFont(fontName, timeFontSize, QFont::Normal));
    temperatureLabel->setFont(QFont(fontName, temperatureFontSize, QFont::Bold));
    maxTemperatureLabel->setFont(QFont(fontName, minmaxTemperatureFontSize, QFont::Normal));
    minTemperatureLabel->setFont(QFont(fontName, minmaxTemperatureFontSize, QFont::Normal));
    iconLabel->setPixmap(weatherIcon.scaled(iconWidth, iconHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedWidth(iconWidth);

    QString labelStyle = "QLabel { color: white; }";
    locationLabel->setStyleSheet(labelStyle);
    locationLabel->setWordWrap(true);
    timeLabel->setStyleSheet(labelStyle);
    temperatureLabel->setStyleSheet(labelStyle);

    leftLayout->addWidget(locationLabel, 0, Qt::AlignCenter);
    leftLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
    leftLayout->addWidget(timeLabel, 0, Qt::AlignCenter);

    rightLayout->addWidget(maxTemperatureLabel, 0, Qt::AlignCenter);
    rightLayout->addWidget(temperatureLabel, 0, Qt::AlignCenter);
    rightLayout->addWidget(minTemperatureLabel, 0, Qt::AlignCenter);

    auto* separator = new QFrame();
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("color: black;");

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(separator);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);
}

int WeatherWidget::adjustLabelFontSize(const QString &fontName)
{
    QFont font(fontName, locationFontSize);
    QFontMetrics fm(font);

    QRect textRect = fm.boundingRect(0, 0, locationLabel->width(), locationFontSize, Qt::AlignCenter | Qt::TextWordWrap, locationLabel->text());
    int textHeight = textRect.height();

    while (textHeight > locationFontSize && fm.height() > 0) {
        font.setPointSize(font.pointSize() - 1);
        fm = QFontMetrics(font);
        textHeight = fm.height();
    }
    return font.pointSize();
}

void WeatherWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit clicked(data->location());
}

void WeatherWidget::setHighlight()
{
    setStyleSheet("WeatherWidget { border-radius: 20px; background-color: #0848F3; }");
}

void WeatherWidget::resetHighlight()
{
    setStyleSheet("WeatherWidget { border-radius: 20px; background-color: #598be0; }");
}


QString WeatherWidget::weatherCodeToIcon(const int weatherCode, const bool isDay) {
    const QString iconBasePath = "../Resources/weatherIcons/";

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
        return iconBasePath + "Cloudy.png";
    }
}


