#include "WeatherData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>


WeatherData::WeatherData(QString& location, int temperature, int highestTemperature, int lowestTemperature, int weatherCode, bool isDay, QTimeZone timezone)
    : location(location)
    , temperature(temperature)
    , highestTemperature(highestTemperature)
    , lowestTemperature(lowestTemperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
    , timezone(timezone)
{
}

