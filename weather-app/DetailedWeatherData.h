#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class GeoLocationData;

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(const GeoLocationData &location,
                                 const int temperature,
                                 const int highestTemperature,
                                 const int lowestTemperature,
                                 const int weatherCode,
                                 const bool isDay,
                                 const QTimeZone &timezone);

    QString location;
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;
    bool isDay;
    QTimeZone timezone;
};

#endif // DETAILEDWEATHERDATA_H

/*class WeatherData : public Data
{
public:

    WeatherData(QString& location,
                int temperature,
                int highestTemperature,
                int lowestTemperature,
                int weatherCode,
                bool isDay,
                QTimeZone timezone);

    QString location;
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;
    bool isDay;
    QTimeZone timezone;
};*/
