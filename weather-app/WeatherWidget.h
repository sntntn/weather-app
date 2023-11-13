#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
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
    QLabel *timeLabel;
    QVBoxLayout *layout;
};

#endif // WEATHERWIDGET_H
