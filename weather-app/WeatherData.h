#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>

#include "Data.h"

class WeatherData : public Data
{
public:
    WeatherData();
    WeatherData(QString& location_, double temperature_, int highestTemperature, int lowestTemperature, int weatherCode);
    QString location;
    int temperature;
    int highestTemperature;
    int lowestTemperature;
    int weatherCode;

};

#endif // WEATHERDATA_H
