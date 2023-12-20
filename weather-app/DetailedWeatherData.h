#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class GeoLocationData;

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(const GeoLocationData &location,
                                 const int temperature,
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
                                 const std::vector<int> weeklyMaxTemp,
                                 const std::vector<int> weeklyMinTemp,
                                 const std::vector<int> weeklyCode,
                                 const std::vector<QString> weeklySunrise,
                                 const std::vector<QString> weeklySunset
                                 );

    GeoLocationData location;
    int temperature;
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
    std::vector<int> weeklyMaxTemp;
    std::vector<int> weeklyMinTemp;
    std::vector<int> weeklyCode;
    std::vector<QString> weeklySunrise;
    std::vector<QString> weeklySunset;
};

#endif // DETAILEDWEATHERDATA_H


