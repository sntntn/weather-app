#include "Parser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <iostream>

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
    QJsonObject hourly = obj.value("hourly").toObject();

    QTimeZone timeZone = QTimeZone(timezoneId.toLatin1());
    int temperature = static_cast<int>(qRound(current.value("temperature_2m").toDouble()));
    int weatherCode = current.value("weather_code").toInt();
    bool isDay = static_cast<bool>(current.value("is_day").toInt());
    int windSpeed = static_cast<int>(qRound(current.value("wind_speed_10m").toDouble()));
    int apparentTemperature = static_cast<int>(qRound(current.value("apparent_temperature").toDouble()));
    int precipitation = static_cast<int>(qRound(current.value("precipitation").toDouble()));
    int humidity = static_cast<int>(qRound(current.value("relative_humidity_2m").toDouble()));
    int visibility = static_cast<int>(qRound(current.value("visibility").toDouble()));
    int pressure =  static_cast<int>(qRound(current.value("pressure_msl").toDouble()));
    int uvIndex = static_cast<int>(qRound(current.value("uv_index").toDouble()));
    int precipitationProbability = static_cast<int>(qRound(current.value("precipitation_probability").toDouble()));
    int windDirection = static_cast<int>(qRound(current.value("wind_direction_10m").toDouble()));
    int windGusts = static_cast<int>(qRound(current.value("wind_gusts_10m").toDouble()));

    qDebug() << "temperature:" << temperature;
    qDebug() << "weatherCode:" << weatherCode;
    qDebug() << "isDay:" << isDay;
    qDebug() << "wind speed:" << windSpeed;
    qDebug() << "real feel:" << apparentTemperature;
    qDebug() << "precipitation:" << precipitation;
    qDebug() << "humidity:" << humidity;
    qDebug() << "visibility:" << visibility;
    qDebug() << "pressure:" << pressure;
    qDebug() << "uv:" << uvIndex;
    qDebug() << "precipitation probability:" << precipitationProbability;
    qDebug() << "wind direction:" << windDirection;
    qDebug() << "wind gusts:" << windGusts;

    QJsonArray hourlyTempJ = hourly.value("temperature_2m").toArray();
    QJsonArray hourlyCodeJ = hourly.value("weather_code").toArray();
    QJsonArray hourlyIsDayJ = hourly.value("is_day").toArray();


    //int weatherCode = current.value("weather_code").toInt();
    //bool isDay = static_cast<bool>(current.value("is_day").toInt());

    std::vector<int> ht;
    std::vector<int> hc;
    std::vector<bool> hd;
    for (int i = 0; i < 24; i++){
        int temperature = static_cast<int>(qRound(hourlyTempJ[i].toDouble()));
        ht.push_back(temperature);
        int code = hourlyCodeJ[i].toInt();
        hc.push_back(code);
        int day = static_cast<bool>(hourlyIsDayJ[i].toInt());
        hd.push_back(day);
    }

    qDebug() << ht;
    qDebug() << hc;
    qDebug() << hd;

    //query.addQueryItem("daily", "weather_code,sunrise,sunset");

    QJsonArray dailyMaxTemperature = daily.value("temperature_2m_max").toArray();
    int maxTemperature = static_cast<int>(qRound(dailyMaxTemperature[0].toDouble()));

    qDebug() << "daily max:" << maxTemperature;

    QJsonArray dailyMinTemperature = daily.value("temperature_2m_min").toArray();
    int minTemperature = static_cast<int>(qRound(dailyMinTemperature[0].toDouble()));

    qDebug() << "daily min:" << minTemperature;

    QJsonArray dailyCodeJ = daily.value("weather_code").toArray();
    int dailyCode = static_cast<int>(qRound(dailyCodeJ[0].toDouble()));

    qDebug() << "daily code:" << dailyCode;

    QJsonArray dailySunriseJ = daily.value("sunrise").toArray();
    QString dailySunrise = static_cast<QString>(dailySunriseJ[0].toString());

    int indexOfT = dailySunrise.indexOf('T');

    if (indexOfT != -1 && indexOfT < dailySunrise.length() - 1)
        dailySunrise = dailySunrise.mid(indexOfT + 1);


    qDebug() << "daily sunrise:" << dailySunrise;

    QJsonArray dailySunsetJ = daily.value("sunset").toArray();
    QString dailySunset = static_cast<QString>(dailySunsetJ[0].toString());

    indexOfT = dailySunset.indexOf('T');

    if (indexOfT != -1 && indexOfT < dailySunset.length() - 1)
        dailySunset = dailySunset.mid(indexOfT + 1);

    qDebug() << "daily sunset:" << dailySunset;



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
                                                                     humidity,
                                                                     visibility,
                                                                     pressure,
                                                                     ht,
                                                                     hc,
                                                                     hd,
                                                                     dailyCode,
                                                                     dailySunrise,
                                                                     dailySunset));



    return data;
}
