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
                                 const int humidity,
                                 const int visibility,
                                 const int pressure,
                                 const std::vector<int> hourlyTemperature,
                                 const std::vector<int> hourlyCode,
                                 const std::vector<bool> hourlyIsDay,
                                 const int dailyCode,
                                 const QString dailySunrise,
                                 const QString dailySunset,
                                 const std::vector<int> weeklyMaxTemp,
                                 const std::vector<int> weeklyMinTemp
                                 );

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
    int humidity;
    int visibility;
    int pressure;
    std::vector<int> hourlyTemperature;
    std::vector<int> hourlyCode;
    std::vector<bool> hourlyIsDay;
    int dailyCode;
    QString dailySunrise;
    QString dailySunset;
    std::vector<int> weeklyMaxTemp;
    std::vector<int> weeklyMinTemp;
};

#endif // DETAILEDWEATHERDATA_H


