#include "WeatherData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>


WeatherData::WeatherData(QString& location, double temperature, int highestTemperature, int lowestTemperature, int weatherCode, bool isDay)
    : location(location)
    , temperature(temperature)
    , highestTemperature(highestTemperature)
    , lowestTemperature(lowestTemperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
{
}

