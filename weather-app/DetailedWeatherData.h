#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(QString& location,
                                 int temperature,
                                 int highestTemperature,
                                 int lowestTemperature,
                                 int weatherCode,
                                 bool isDay,
                                 QTimeZone &timezone);
};

#endif // DETAILEDWEATHERDATA_H
