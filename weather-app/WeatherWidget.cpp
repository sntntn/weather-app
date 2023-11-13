#include "WeatherWidget.h"
#include <QString>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QFont>
#include <QPalette>
#include <QFrame>

WeatherWidget::WeatherWidget(QWidget *parent, WeatherData* data_)
    : QWidget{parent},
    data(data_),
    locationLabel(new QLabel(data->location, this)),
    temperatureLabel(new QLabel(QString::number(data->temperature), this)),
    timeLabel(new QLabel(QTime::currentTime().toString("HH:mm"), this)),
    layout(new QVBoxLayout(this))
{
    layout->setSpacing(5);
    layout->setContentsMargins(10, 10, 10, 10);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("WeatherWidget { border-radius: 20px; background-color: #598be0; }");

    locationLabel->setFont(QFont("Arial", 18, QFont::Bold));
    timeLabel->setFont(QFont("Arial", 14, QFont::Normal));
    temperatureLabel->setFont(QFont("Arial", 24, QFont::Bold));

    QString labelStyle = "QLabel { color: white; }";
    locationLabel->setStyleSheet(labelStyle);
    timeLabel->setStyleSheet(labelStyle);
    temperatureLabel->setStyleSheet(labelStyle);

    layout->addWidget(locationLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(temperatureLabel, 0, Qt::AlignRight);

    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

WeatherWidget::~WeatherWidget()
{
    delete data;
    delete locationLabel;
    delete temperatureLabel;
}
