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
    , weatherIcon(Settings::instance().weatherCodeToIcon(data->weatherCode(), data->isDay()))
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

    locationLabel->setStyleSheet("color: white;");
    locationLabel->setWordWrap(true);
    timeLabel->setStyleSheet("color: white;");
    temperatureLabel->setStyleSheet("color: white;");

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

    const int fmHeight = fm.height();
    while (textHeight > locationFontSize && fmHeight > 0) {
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
