#include "DetailedWeatherData.h"
#include <iostream>

DetailedWeatherData::DetailedWeatherData(const GeoLocationData &location,
                                         const int temperature,
                                         const int weatherCode,
                                         const bool isDay,
                                         const QTimeZone &timezone,
                                         const int windSpeed,
                                         const int windGusts,
                                         const int windDirection,
                                         const int apparentTemperature,
                                         const int precipitation,
                                         const int uvIndex,
                                         const int humidity,
                                         const int visibility,
                                         const int pressure,
                                         const std::vector<int> hourlyTemperature,
                                         const std::vector<int> hourlyCode,
                                         const std::vector<bool> hourlyIsDay,
                                         const std::vector<QString> hourlyTimeStamp,
                                         const std::vector<int> weeklyMaxTemp,
                                         const std::vector<int> weeklyMinTemp,
                                         const std::vector<int> weeklyCode,
                                         const std::vector<QString> weeklySunrise,
                                         const std::vector<QString> weeklySunset
                                         )

    : WeatherData(location, temperature, weeklyMaxTemp[0], weeklyMinTemp[0], weatherCode, isDay, timezone)
    , location(location)
    , temperature(temperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
    , timezone(timezone)
    , windSpeed(windSpeed)
    , windGusts(windGusts)
    , windDirection(windDirection)
    , apparentTemperature(apparentTemperature)
    , precipitation(precipitation)
    , uvIndex(uvIndex)
    , humidity(humidity)
    , visibility(visibility)
    , pressure(pressure)
    , hourlyTemperature(hourlyTemperature)
    , hourlyCode(hourlyCode)
    , hourlyIsDay(hourlyIsDay)
    , hourlyTimeStamp(hourlyTimeStamp)
    , weeklyMaxTemp(weeklyMaxTemp)
    , weeklyMinTemp(weeklyMinTemp)
    , weeklyCode(weeklyCode)
    , weeklySunrise(weeklySunrise)
    , weeklySunset(weeklySunset)
{}

