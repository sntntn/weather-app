#include "Parser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "WeatherData.h"

Parser::Parser() = default;

WeatherData* Parser::parseWeatherData(const QString& jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject obj = doc.object();
    QJsonObject current = obj.value("current").toObject();

    QString location = QString::fromStdString("Belgrade"); // test, TODO
    double temperature = current.value("temperature_2m").toDouble();
    double windSpeed = current.value("wind_speed_10m").toDouble();
    double rain = current.value("rain").toDouble();
    auto *data = new WeatherData(location, temperature, windSpeed, rain);

    return data;
}
