#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>
#include <QTimeZone>

#include "Data.h"

class WeatherData : public Data
{
public:

    WeatherData(const QString& location,
                int temperature,
                int highestTemperature,
                int lowestTemperature,
                int weatherCode,
                bool isDay,
                QTimeZone &timezone);

    QString location;
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;
    bool isDay;
    QTimeZone timezone;
};

#endif // WEATHERDATA_H
