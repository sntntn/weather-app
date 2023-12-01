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
    QString timezoneId = obj.value("timezone").toString();
    QJsonObject current = obj.value("current").toObject();
    QJsonObject daily = obj.value("daily").toObject();


    QString location = QString::fromStdString("Belgrade"); // test, TODO

    QTimeZone timeZone = QTimeZone(timezoneId.toLatin1());

    int temperature = static_cast<int>(qRound(current.value("temperature_2m").toDouble()));
    int weatherCode = current.value("weather_code").toInt();
    bool isDay = static_cast<bool>(current.value("is_day").toInt());

    QJsonArray dailyMaxTemperature = daily.value("temperature_2m_max").toArray();
    int maxTemperature = static_cast<int>(qRound(dailyMaxTemperature[0].toDouble()));

    QJsonArray dailyMinTemperature = daily.value("temperature_2m_min").toArray();
    int minTemperature = static_cast<int>(qRound(dailyMinTemperature[0].toDouble()));

    QSharedPointer<WeatherData> data(new WeatherData(location,
                                                     temperature,
                                                     maxTemperature,
                                                     minTemperature,
                                                     weatherCode,
                                                     isDay,
                                                     timeZone));

    return data;
}
