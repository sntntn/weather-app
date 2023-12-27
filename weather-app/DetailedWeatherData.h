#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class GeoLocationData;

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(const GeoLocationData &location,
                                 const int temperature,
                                 const int weatherCode,
                                 const bool isDay,
                                 const QTimeZone &timezone,
                                 const int windSpeed,
                                 const int windGusts,
                                 const int windDirection,
                                 const int apparentTemperature,
                                 const int precipitation,
                                 const int uvIndex,
                                 const int humidity,
                                 const int visibility,
                                 const int pressure,
                                 const QVector<int> &hourlyTemperature,
                                 const QVector<int> &hourlyCode,
                                 const QVector<bool> &hourlyIsDay,
                                 const QVector<QString> &hourlyTimeStamp,
                                 const QVector<int> &weeklyMaxTemp,
                                 const QVector<int> &weeklyMinTemp,
                                 const QVector<int> &weeklyCode,
                                 const QVector<QString> &weeklySunrise,
                                 const QVector<QString> &weeklySunset,
                                 const QVector<QString> &weeklyDayName
                                 );

    inline GeoLocationData location() const
    {
        return m_location;
    }
    inline int temperature() const
    {
        return m_temperature;
    };
    inline int weatherCode() const
    {
        return m_weatherCode;
    }
    inline bool isDay() const
    {
        return m_isDay;
    }
    inline QTimeZone timezone() const
    {
        return m_timezone;
    }
    inline int windSpeed() const
    {
        return m_windSpeed;
    }
    inline int windGusts() const
    {
        return m_windGusts;
    }
    inline int windDirection() const
    {
        return m_windDirection;
    }
    inline int apparentTemperature() const
    {
        return m_apparentTemperature;
    }
    inline int precipitation() const
    {
        return m_precipitation;
    }
    inline int uvIndex() const
    {
        return m_uvIndex;
    }
    inline int humidity() const
    {
        return m_humidity;
    }
    inline int visibility() const
    {
        return m_visibility;
    }
    inline int pressure() const
    {
        return m_pressure;
    }
    inline QVector<int> hourlyTemperature() const
    {
        return m_hourlyTemperature;
    }
    inline QVector<int> hourlyCode() const
    {
        return m_hourlyCode;
    }
    inline QVector<bool> hourlyIsDay() const
    {
        return m_hourlyIsDay;
    }
    inline QVector<QString> hourlyTimeStamp() const
    {
        return m_hourlyTimeStamp;
    }
    inline QVector<int> weeklyMaxTemp() const
    {
        return m_weeklyMaxTemp;
    }
    inline QVector<int> weeklyMinTemp() const
    {
        return m_weeklyMinTemp;
    }
    inline QVector<int> weeklyCode() const
    {
        return m_weeklyCode;
    }
    inline QVector<QString> weeklySunrise() const
    {
        return m_weeklySunrise;
    }
    inline QVector<QString> weeklySunset() const
    {
        return m_weeklySunset;
    }
    inline QVector<QString> weeklyDayName() const
    {
        return m_weeklyDayName;
    }

private:
    GeoLocationData m_location;
    int m_temperature;
    int m_highestTemperature;
    int m_lowestTemperature;
    int m_weatherCode;
    bool m_isDay;
    QTimeZone m_timezone;
    int m_windSpeed;
    int m_windGusts;
    int m_windDirection;
    int m_apparentTemperature;
    int m_precipitation;
    int m_uvIndex;
    int m_humidity;
    int m_visibility;
    int m_pressure;
    QVector<int> m_hourlyTemperature;
    QVector<int> m_hourlyCode;
    QVector<bool> m_hourlyIsDay;
    QVector<QString> m_hourlyTimeStamp;
    QVector<int> m_weeklyMaxTemp;
    QVector<int> m_weeklyMinTemp;
    QVector<int> m_weeklyCode;
    QVector<QString> m_weeklySunrise;
    QVector<QString> m_weeklySunset;
    QVector<QString> m_weeklyDayName;

};

#endif // DETAILEDWEATHERDATA_H


