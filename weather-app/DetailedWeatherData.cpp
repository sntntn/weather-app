#include "DetailedWeatherData.h"

DetailedWeatherData::DetailedWeatherData(QString& location,
                                         double temperature,
                                         int highestTemperature,
                                         int lowestTemperature,
                                         int weatherCode,
                                         bool isDay)
    : WeatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay)
{ }
