#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>

#include "Data.h"

class WeatherData : public Data
{
public:
    WeatherData(QString& location,
                double temperature,
                int highestTemperature,
                int lowestTemperature,
                int weatherCode);

    QString location;
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;
    bool isDay;
};

#endif // WEATHERDATA_H
