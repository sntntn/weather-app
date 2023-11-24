#include "WeatherData.h"

WeatherData::WeatherData(QString& location_,
                         double temperature_,
                         double windSpeed_,
                         double rain_)
    : location(location_)
    , temperature(temperature_)
    , windSpeed(windSpeed_)
    , rain(rain_)
{ }
