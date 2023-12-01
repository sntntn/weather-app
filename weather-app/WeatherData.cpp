#include "WeatherData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

WeatherData::WeatherData()
{
}

WeatherData::WeatherData(QString& location_,
                         double temperature_,
                         double windSpeed_,
                         double rain_)
    : location(location_)
    , temperature(temperature_)
    , windSpeed(windSpeed_)
    , rain(rain_)
{
}

