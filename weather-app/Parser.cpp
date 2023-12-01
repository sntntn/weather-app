#include "Parser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "WeatherData.h"
#include "DetailedWeatherData.h"

Parser::Parser() = default;

QSharedPointer<WeatherData> Parser::parseWeatherData(const QString& jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject obj = doc.object();
    QJsonObject current = obj.value("current").toObject();
    QJsonObject daily = obj.value("daily").toObject();


    QString location = QString::fromStdString("Belgrade"); // test, TODO

    int temperature = current.value("temperature_2m").toInt();
    int weatherCode = current.value("weather_code").toInt();
    bool isDay = current.value("is_day").toInt();

    QJsonArray dailyMaxTemperature = daily.value("temperature_2m_max").toArray();
    int maxTemperature = qRound(dailyMaxTemperature[0].toDouble());

    QJsonArray dailyMinTemperature = daily.value("temperature_2m_min").toArray();
    int minTemperature = qRound(dailyMinTemperature[0].toDouble());

    QSharedPointer<WeatherData> data(new WeatherData(location,
                                                     temperature,
                                                     maxTemperature,
                                                     minTemperature,
                                                     weatherCode,
                                                     isDay));

    return data;
}

QSharedPointer<DetailedWeatherData> Parser::parseDetailedWeatherData(const QString& jsonData)
{
    // todo
    return nullptr;
}
