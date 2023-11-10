#include "WeatherWidget.h"
#include <QString>

WeatherWidget::WeatherWidget(QWidget *parent, WeatherData* data_)
    : QWidget{parent},
    data(data_),
    locationLabel(new QLabel(data->location, this)),
    temperatureLabel(new QLabel(QString::number(data->temperature), this))
{
    locationLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    temperatureLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);

    locationLabel->setGeometry(0, 0, width(), height());
    temperatureLabel->setGeometry(0, 0, width(), height());
}

WeatherWidget::~WeatherWidget()
{
    delete data;
    delete locationLabel;
    delete temperatureLabel;
}
