#include "WeatherData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

#include "GeoLocationData.h"

WeatherData::WeatherData(const GeoLocationData &location, int temperature, int highestTemperature, int lowestTemperature, int weatherCode, bool isDay, QTimeZone& timezone)
    : location(location)
    , temperature(temperature)
    , highestTemperature(highestTemperature)
    , lowestTemperature(lowestTemperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
    , timezone(timezone)
{
}

