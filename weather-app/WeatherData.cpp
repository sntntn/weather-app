#include "WeatherData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

#include "GeoLocationData.h"

WeatherData::WeatherData(const GeoLocationData &location,
                         const int temperature,
                         const int highestTemperature,
                         const int lowestTemperature,
                         const int weatherCode,
                         const bool isDay,
                         const QTimeZone& timezone)
    : location(location)
    , temperature(temperature)
    , highestTemperature(highestTemperature)
    , lowestTemperature(lowestTemperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
    , timezone(timezone)
{ }

