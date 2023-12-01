#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(QString& location,
                                 double temperature,
                                 int highestTemperature,
                                 int lowestTemperature,
                                 int weatherCode);
};

#endif // DETAILEDWEATHERDATA_H
