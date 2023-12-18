#include "DetailedWeatherData.h"
#include <iostream>

DetailedWeatherData::DetailedWeatherData(const GeoLocationData &location,
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
                                         )

    : WeatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay, timezone)
    , location(location)
    , temperature(temperature)
    , highestTemperature(highestTemperature)
    , lowestTemperature(lowestTemperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
    , timezone(timezone)
    , windSpeed(windSpeed)
    , apparentTemperature(apparentTemperature)
    , precipitation(precipitation)
    , uvIndex(uvIndex)
    , humidity(humidity)
    , visibility(visibility)
    , pressure(pressure)
    , hourlyTemperature(hourlyTemperature)
    , hourlyCode(hourlyCode)
    , hourlyIsDay(hourlyIsDay)
    , dailyCode(dailyCode)
    , dailySunrise(dailySunrise)
    , dailySunset(dailySunset)
    , weeklyMaxTemp(weeklyMaxTemp)
    , weeklyMinTemp(weeklyMinTemp)

{}

