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
    : BasicWidget{parent}
    , data(data)
    , leftLayout(new QVBoxLayout())
    , rightLayout(new QVBoxLayout())
    , temperatureLabel(new QLabel(QString::number(data->temperature()) + "°", this))
    , locationLabel(new QLabel(data->location().getRenamedPlace().toUpper(), this))
    , countryLabel(new QLabel(data->location().getCountry(), this))
    , maxTemperatureLabel(new QLabel("H:" + QString::number(data->highestTemperature()) + "°", this))
    , minTemperatureLabel(new QLabel("L:" + QString::number(data->lowestTemperature()) + "°", this))
    , timeLabel(new QLabel(QDateTime::currentDateTime().toTimeZone(data->timezone()).toString("HH:mm"), this))
    , iconLabel(new QLabel(this))
    , weatherIcon(Settings::instance().weatherCodeToIcon(data->weatherCode(), data->isDay()))
{
    mainLayout->setSpacing(hBoxSpacing);
    mainLayout->setContentsMargins(hBoxMarginSize, hBoxMarginSize, hBoxMarginSize, hBoxMarginSize);

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

    countryLabel->setFont(QFont(fontName, adjustCountryLabelFontSize(fontName), QFont::Normal));
    countryLabel->setStyleSheet("QLabel { color: #cccccc; }");
    countryLabel->setWordWrap(true);

    leftLayout->addWidget(locationLabel, 0, Qt::AlignCenter);
    leftLayout->addSpacing(-10);
    leftLayout->addWidget(countryLabel, 0, Qt::AlignCenter);
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


//TO DO
//test funkcija za prilagodjavanje fonta i velicine countryLabel    -> za slucaj da GUI kolege zele drugacije da ga pozicioniraju i preurede :)
int WeatherWidget::adjustCountryLabelFontSize(const QString &fontName)
{
    QString countryText = data->location().getCountry();

    int countryLabelFontSize = initialFontSize - 8;
    QFont font(fontName, countryLabelFontSize);
    QFontMetrics fm(font);

    QRect textRect = fm.boundingRect(0, 0, countryLabel->width(), QWIDGETSIZE_MAX, Qt::TextWordWrap, countryText);
    int textHeight = textRect.height();

    int maxHeight = countryLabel->maximumHeight();
    int minFontSize = 8;

    while (textHeight > maxHeight && font.pointSize() > minFontSize) {
        font.setPointSize(font.pointSize() - 1);
        fm = QFontMetrics(font);
        textRect = fm.boundingRect(0, 0, countryLabel->width(), QWIDGETSIZE_MAX, Qt::TextWordWrap, countryText);
        textHeight = textRect.height();
    }

    countryLabel->setFont(font);

    return font.pointSize();
}


int WeatherWidget::adjustLabelFontSize(const QString &fontName)
{
    QFont font(fontName, initialFontSize);
    QFontMetrics fm(font);

    QRect textRect = fm.boundingRect(0, 0, countryLabel->width(), initialFontSize, Qt::AlignCenter | Qt::TextWordWrap, countryLabel->text());
    int textHeight = textRect.height();

    const int fmHeight = fm.height();
    while (textHeight > initialFontSize && fmHeight> 0) {
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
