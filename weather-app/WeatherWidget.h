#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include "WeatherData.h"

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(QWidget *parent = nullptr, WeatherData *data_ = nullptr);
    ~WeatherWidget();

signals:

private:
    WeatherData* data;
    QLabel* locationLabel;
    QLabel* temperatureLabel;

};

#endif // WEATHERWIDGET_H
