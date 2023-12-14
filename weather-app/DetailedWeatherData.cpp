#include "DetailedWeatherData.h"

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
                                         const int weeklyLowestTemperature)
    : WeatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay, timezone)
    , windSpeed(windSpeed)
    , apparentTemperature(apparentTemperature)
    , precipitation(precipitation)
    , uvIndex(uvIndex)
    , weeklyHighestTemperature(weeklyHighestTemperature)
    , weeklyLowestTemperature(weeklyLowestTemperature)
{ }

