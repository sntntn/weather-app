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
                                 const QTimeZone &timezone,
                                 const int windSpeed,
                                 const int apparentTemperature,
                                 const int precipitation,
                                 const int uvIndex,
                                 const int weeklyHighestTemperature,
                                 const int weeklyLowestTemperature,
                                 const int humidity,
                                 const int visibility,
                                 const int pressure);

    GeoLocationData location;
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;
    bool isDay;
    QTimeZone timezone;
    int windSpeed;
    int apparentTemperature;
    int precipitation;
    int uvIndex;
    int weeklyHighestTemperature;
    int weeklyLowestTemperature;
    int humidity;
    int visibility;
    int pressure;
};

#endif // DETAILEDWEATHERDATA_H


