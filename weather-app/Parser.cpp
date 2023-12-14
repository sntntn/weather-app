#include "Parser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "WeatherData.h"
#include "DetailedWeatherData.h"
#include "GeoLocationData.h"

Parser::Parser() = default;

QSharedPointer<WeatherData> Parser::parseWeatherData(const QString& jsonData, const GeoLocationData &geoLocation)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject obj = doc.object();
    QString timezoneId = obj.value("timezone").toString();
    QJsonObject current = obj.value("current").toObject();
    QJsonObject daily = obj.value("daily").toObject();

    QTimeZone timeZone = QTimeZone(timezoneId.toLatin1());
    int temperature = static_cast<int>(qRound(current.value("temperature_2m").toDouble()));
    int weatherCode = current.value("weather_code").toInt();
    bool isDay = static_cast<bool>(current.value("is_day").toInt());

    QJsonArray dailyMaxTemperature = daily.value("temperature_2m_max").toArray();
    int maxTemperature = static_cast<int>(qRound(dailyMaxTemperature[0].toDouble()));

    QJsonArray dailyMinTemperature = daily.value("temperature_2m_min").toArray();
    int minTemperature = static_cast<int>(qRound(dailyMinTemperature[0].toDouble()));

    QSharedPointer<WeatherData> data(new WeatherData(geoLocation,
                                                     temperature,
                                                     maxTemperature,
                                                     minTemperature,
                                                     weatherCode,
                                                     isDay,
                                                     timeZone));

    return data;
}

QSharedPointer<DetailedWeatherData> Parser::parseDetailedWeatherData(const QString& jsonData, const GeoLocationData &geoLocation)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject obj = doc.object();
    QString timezoneId = obj.value("timezone").toString();
    QJsonObject current = obj.value("current").toObject();
    QJsonObject daily = obj.value("daily").toObject();

    QTimeZone timeZone = QTimeZone(timezoneId.toLatin1());
    int temperature = static_cast<int>(qRound(current.value("temperature_2m").toDouble()));
    int weatherCode = current.value("weather_code").toInt();
    bool isDay = static_cast<bool>(current.value("is_day").toInt());
    int windSpeed = static_cast<int>(qRound(current.value("wind_speed_10m").toDouble()));
    int apparentTemperature = static_cast<int>(qRound(current.value("apparent_temperature").toDouble()));
    int precipitation = static_cast<int>(qRound(current.value("precipitation").toDouble()));

    QJsonArray dailyMaxTemperature = daily.value("temperature_2m_max").toArray();
    int maxTemperature = static_cast<int>(qRound(dailyMaxTemperature[0].toDouble()));

    QJsonArray dailyMinTemperature = daily.value("temperature_2m_min").toArray();
    int minTemperature = static_cast<int>(qRound(dailyMinTemperature[0].toDouble()));

    QJsonArray dailyUV = daily.value("uv_index_max").toArray();
    int uvIndex = static_cast<int>(qRound(dailyUV[0].toDouble()));

    QJsonArray weeklyMax = daily.value("temperature_2m_max").toArray();
    int weeklyHighestTemperature = static_cast<int>(qRound(weeklyMax[0].toDouble()));

    QJsonArray weeklyMin = daily.value("temperature_2m_min").toArray();
    int weeklyLowestTemperature = static_cast<int>(qRound(weeklyMin[0].toDouble()));

    QSharedPointer<DetailedWeatherData> data(new DetailedWeatherData(geoLocation,
                                                                     temperature,
                                                                     maxTemperature,
                                                                     minTemperature,
                                                                     weatherCode,
                                                                     isDay,
                                                                     timeZone,
                                                                     windSpeed,
                                                                     apparentTemperature,
                                                                     precipitation,
                                                                     uvIndex,
                                                                     weeklyHighestTemperature,
                                                                     weeklyLowestTemperature));



    return data;
}
