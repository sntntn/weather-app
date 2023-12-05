#include "DetailedWeatherData.h"

DetailedWeatherData::DetailedWeatherData(QString& location,
                                         int temperature,
                                         int highestTemperature,
                                         int lowestTemperature,
                                         int weatherCode,
                                         bool isDay,
                                         QTimeZone &timezone)
    : WeatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay, timezone)
{ }
