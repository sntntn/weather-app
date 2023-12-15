#include "DetailedWeatherData.h"
#include <iostream>

DetailedWeatherData::DetailedWeatherData(const GeoLocationData &location,
                                         const int temperature,
                                         const int highestTemperature,
                                         const int lowestTemperature,
                                         const int weatherCode,
                                         const bool isDay,
                                         const QTimeZone &timezone,
                                         const int windSpeed,
                                         const int apparentTemperature,
                                         const int precipitation,
                                         const int uvIndex,
                                         const int weeklyHighestTemperature,
                                         const int weeklyLowestTemperature,
                                         const int humidity,
                                         const int visibility,
                                         const int pressure,
                                         const int h1,
                                         const int h2,
                                         const int h3,
                                         const int h4,
                                         const int h5,
                                         const int h6,
                                         const int h7,
                                         const int h8,
                                         const int h9,
                                         const int h10,
                                         const int h11,
                                         const int h12,
                                         const int h13,
                                         const int h14,
                                         const int h15,
                                         const int h16,
                                         const int h17,
                                         const int h18,
                                         const int h19,
                                         const int h20,
                                         const int h21,
                                         const int h22,
                                         const int h23,
                                         const int h24)

    : WeatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay, timezone)
    , location(location)
    , temperature(temperature)
    , highestTemperature(highestTemperature)
    , lowestTemperature(lowestTemperature)
    , weatherCode(weatherCode)
    , isDay(isDay)
    , timezone(timezone)
    , windSpeed(windSpeed)
    , apparentTemperature(apparentTemperature)
    , precipitation(precipitation)
    , uvIndex(uvIndex)
    , weeklyHighestTemperature(weeklyHighestTemperature)
    , weeklyLowestTemperature(weeklyLowestTemperature)
    , humidity(humidity)
    , visibility(visibility)
    , pressure(pressure)
    , h1(h1)
    , h2(h2)
    , h3(h3)
    , h4(h4)
    , h5(h5)
    , h6(h6)
    , h7(h7)
    , h8(h8)
    , h9(h9)
    , h10(h10)
    , h11(h11)
    , h12(h12)
    , h13(h13)
    , h14(h14)
    , h15(h15)
    , h16(h16)
    , h17(h17)
    , h18(h18)
    , h19(h19)
    , h20(h20)
    , h21(h21)
    , h22(h22)
    , h23(h23)
    , h24(h24)
{}

