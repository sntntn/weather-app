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
                                         const int weeklyHighestTemperature,
                                         const int weeklyLowestTemperature,
                                         const int humidity,
                                         const int visibility,
                                         const int pressure)

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
    , weeklyHighestTemperature(weeklyHighestTemperature)
    , weeklyLowestTemperature(weeklyLowestTemperature)
    , humidity(humidity)
    , visibility(visibility)
    , pressure(pressure)
{}

