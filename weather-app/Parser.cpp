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

    qDebug() << "temperature:" << temperature;
    qDebug() << "weatherCode:" << weatherCode;
    qDebug() << "isDay:" << isDay;
    qDebug() << "wind speed:" << windSpeed;
    qDebug() << "real feel:" << apparentTemperature;
    qDebug() << "precipitation:" << precipitation;
    qDebug() << "humidity:" << humidity;
    qDebug() << "visibility:" << visibility;
    qDebug() << "pressure:" << pressure;

    QJsonArray poSatima = hourly.value("temperature_2m").toArray();
    int h1 = static_cast<int>(qRound(poSatima[0].toDouble()));
    int h2 = static_cast<int>(qRound(poSatima[1].toDouble()));
    int h3 = static_cast<int>(qRound(poSatima[2].toDouble()));
    int h4 = static_cast<int>(qRound(poSatima[3].toDouble()));
    int h5 = static_cast<int>(qRound(poSatima[4].toDouble()));
    int h6 = static_cast<int>(qRound(poSatima[5].toDouble()));
    int h7 = static_cast<int>(qRound(poSatima[6].toDouble()));
    int h8 = static_cast<int>(qRound(poSatima[7].toDouble()));
    int h9 = static_cast<int>(qRound(poSatima[8].toDouble()));
    int h10 = static_cast<int>(qRound(poSatima[9].toDouble()));
    int h11 = static_cast<int>(qRound(poSatima[10].toDouble()));
    int h12 = static_cast<int>(qRound(poSatima[11].toDouble()));
    int h13 = static_cast<int>(qRound(poSatima[12].toDouble()));
    int h14 = static_cast<int>(qRound(poSatima[13].toDouble()));
    int h15 = static_cast<int>(qRound(poSatima[14].toDouble()));
    int h16 = static_cast<int>(qRound(poSatima[15].toDouble()));
    int h17 = static_cast<int>(qRound(poSatima[16].toDouble()));
    int h18 = static_cast<int>(qRound(poSatima[17].toDouble()));
    int h19 = static_cast<int>(qRound(poSatima[18].toDouble()));
    int h20 = static_cast<int>(qRound(poSatima[19].toDouble()));
    int h21 = static_cast<int>(qRound(poSatima[20].toDouble()));
    int h22 = static_cast<int>(qRound(poSatima[21].toDouble()));
    int h23 = static_cast<int>(qRound(poSatima[22].toDouble()));
    int h24 = static_cast<int>(qRound(poSatima[23].toDouble()));

    qDebug() << "poSatima:" << poSatima;
    qDebug() << "h1:" << h1;
    qDebug() << "h2:" << h2;
    qDebug() << "h3:" << h3;
    qDebug() << "h4:" << h4;
    qDebug() << "h5:" << h5;
    qDebug() << "h6:" << h6;
    qDebug() << "h7:" << h7;
    qDebug() << "h8:" << h8;
    qDebug() << "h9:" << h9;
    qDebug() << "h10:" << h10;
    qDebug() << "h11:" << h11;
    qDebug() << "h12:" << h12;
    qDebug() << "h13:" << h13;
    qDebug() << "h14:" << h14;
    qDebug() << "h15:" << h15;
    qDebug() << "h16:" << h16;
    qDebug() << "h17:" << h17;
    qDebug() << "h18:" << h18;
    qDebug() << "h19:" << h19;
    qDebug() << "h20:" << h20;
    qDebug() << "h21:" << h21;
    qDebug() << "h22:" << h22;
    qDebug() << "h23:" << h23;
    qDebug() << "h24:" << h24;

    QJsonArray dailyMaxTemperature = daily.value("temperature_2m_max").toArray();
    int maxTemperature = static_cast<int>(qRound(dailyMaxTemperature[0].toDouble()));

    qDebug() << "daily max:" << maxTemperature;

    QJsonArray dailyMinTemperature = daily.value("temperature_2m_min").toArray();
    int minTemperature = static_cast<int>(qRound(dailyMinTemperature[0].toDouble()));

    qDebug() << "daily min:" << minTemperature;

    QJsonArray dailyUV = daily.value("uv_index_max").toArray();
    int uvIndex = static_cast<int>(qRound(dailyUV[0].toDouble()));

    qDebug() << "uv:" << uvIndex;

    QJsonArray weeklyMax = daily.value("temperature_2m_max").toArray();
    int weeklyHighestTemperature = static_cast<int>(qRound(weeklyMax[0].toDouble()));

    qDebug() << "weekly max:" << weeklyHighestTemperature;

    QJsonArray weeklyMin = daily.value("temperature_2m_min").toArray();
    int weeklyLowestTemperature = static_cast<int>(qRound(weeklyMin[0].toDouble()));

    qDebug() << "weekly min:" << weeklyLowestTemperature;

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
                                                                     weeklyLowestTemperature,
                                                                     humidity,
                                                                     visibility,
                                                                     pressure,
                                                                     h1, h2, h3, h4, h5, h6, h7, h8, h9, h10,
                                                                     h11, h12, h13, h14, h15, h16, h17, h18, h19, h20, h21, h22, h23, h24));



    return data;
}
