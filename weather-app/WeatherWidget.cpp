#include "WeatherWidget.h"

#include <QString>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QFont>
#include <QPalette>
#include <QFrame>

#include "WeatherData.h"

WeatherWidget::WeatherWidget(const QSharedPointer<WeatherData> &data_, QWidget *parent)
    : QWidget{parent}
    , data(data_)
    , hBox(new QHBoxLayout(this))
    , leftVBox(new QVBoxLayout())
    , rightVBox(new QVBoxLayout())
    , locationLabel(new QLabel(data->location, this))
    , temperatureLabel(new QLabel(QString::number(data->temperature), this))
    , minmaxTemperatureLabel(new QLabel("H:" + QString::number(data->highestTemperature) + " L:" + QString::number(data->lowestTemperature), this))
    , timeLabel(new QLabel(QTime::currentTime().toString("HH:mm"), this))
    , iconLabel(new QLabel(this))
    , weatherIcon("../Resources/weatherIcons/PartlyCloudyDay.png") // test
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
    //iconLabel->setPixmap(weatherIcon.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QString labelStyle = "QLabel { color: white; }";
    locationLabel->setStyleSheet(labelStyle);
    timeLabel->setStyleSheet(labelStyle);
    temperatureLabel->setStyleSheet(labelStyle);

    QHBoxLayout* hLayout = new QHBoxLayout();
    //QSpacerItem* spacer = new QSpacerItem();
    hLayout->addStretch();
    hLayout->addWidget(temperatureLabel);
    //hLayout->addWidget(iconLabel);

    leftVBox->addWidget(locationLabel);
    leftVBox->addWidget(timeLabel);
    //rightVBox->addWidget(iconLabel, 0, Qt::AlignTop | Qt::AlignRight);
    //rightVBox->addWidget(temperatureLabel, 0, Qt::AlignTop | Qt::AlignRight);
    rightVBox->addLayout(hLayout);
    rightVBox->addWidget(minmaxTemperatureLabel, 0, Qt::AlignBottom | Qt::AlignRight);

    setLayout(hBox);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

}

void WeatherWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked(data);
}

WeatherWidget::~WeatherWidget()
{
    delete hBox;
    delete leftVBox;
    delete rightVBox;
    delete locationLabel;
    delete temperatureLabel;
    delete timeLabel;
    delete iconLabel;
}
