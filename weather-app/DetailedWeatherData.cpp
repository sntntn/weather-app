#include "DetailedWeatherData.h"


DetailedWeatherData::DetailedWeatherData(const GeoLocationData &location,
                                         const int temperature,
                                         const int highestTemperature,
                                         const int lowestTemperature,
                                         const int weatherCode,
                                         const bool isDay,
                                         const QTimeZone &timezone)
    : WeatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay, timezone)
{ }
