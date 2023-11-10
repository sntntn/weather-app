#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>

class WeatherData
{
public:
    WeatherData();
    WeatherData(QString location_, double temperature_, double windSpeed_, double rain_);
    QString location;
    double temperature;
    double windSpeed;
    double rain;
};

#endif // WEATHERDATA_H
