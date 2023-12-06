#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>
#include <QTimeZone>

#include "Data.h"
#include "GeoLocationData.h"

class WeatherData : public Data
{
public:

    WeatherData(const GeoLocationData &location, // todo sharedptr, const sve
                int temperature,
                int highestTemperature,
                int lowestTemperature,
                int weatherCode,
                bool isDay,
                QTimeZone &timezone);

    GeoLocationData location; // todo sharedptr
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;
    bool isDay;
    QTimeZone timezone;
};

#endif // WEATHERDATA_H
