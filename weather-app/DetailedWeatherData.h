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
                                 const int pressure,
                                 const int h1,
                                 const int h2,
                                 const int h3,
                                 const int h4,
                                 const int h5,
                                 const int h6,
                                 const int h7,
                                 const int h8,
                                 const int h9,
                                 const int h10,
                                 const int h11,
                                 const int h12,
                                 const int h13,
                                 const int h14,
                                 const int h15,
                                 const int h16,
                                 const int h17,
                                 const int h18,
                                 const int h19,
                                 const int h20,
                                 const int h21,
                                 const int h22,
                                 const int h23,
                                 const int h24);

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
    int h1;
    int h2;
    int h3;
    int h4;
    int h5;
    int h6;
    int h7;
    int h8;
    int h9;
    int h10;
    int h11;
    int h12;
    int h13;
    int h14;
    int h15;
    int h16;
    int h17;
    int h18;
    int h19;
    int h20;
    int h21;
    int h22;
    int h23;
    int h24;
};

#endif // DETAILEDWEATHERDATA_H


