#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class GeoLocationData;

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(GeoLocationData &location,
                                 int temperature,
                                 int highestTemperature,
                                 int lowestTemperature,
                                 int weatherCode,
                                 bool isDay,
                                 QTimeZone &timezone);
};

#endif // DETAILEDWEATHERDATA_H
