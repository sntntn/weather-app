#include "Parser.h"

#include "WeatherData.h"
#include "GeoLocationData.h"

WeatherData* Parser::parseWeatherData(const QString &jsonData, const GeoLocationData &geoLocation)
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

    return new WeatherData(geoLocation,
                           temperature,
                           maxTemperature,
                           minTemperature,
                           weatherCode,
                           isDay,
                           timeZone);
}

void Parser::parseGeocodingData(const QJsonArray &resultsArray, QList<GeoLocationData> &locations)
{
    for (auto resultValue : resultsArray) {
        QJsonObject resultObject = resultValue.toObject();

        if (!resultObject.contains("formatted") || !resultObject["formatted"].isString()) {
            continue;
        }

        QString place = resultObject["formatted"].toString();
        if(!place.isEmpty() && place.at(0).isDigit()){
            continue;
        }

        if (!resultObject.contains("geometry") || !resultObject["geometry"].isObject()) {
            continue;
        }

        QJsonObject geometryObject = resultObject["geometry"].toObject();
        if (!geometryObject.contains("lat") || !geometryObject.contains("lng")) {
            continue;
        }

        double latitude = geometryObject["lat"].toDouble();
        double longitude = geometryObject["lng"].toDouble();

        QString renamedPlace;
        auto commaIndex=place.indexOf(',');
        commaIndex == -1 ? renamedPlace = place : renamedPlace = place.left(commaIndex).trimmed();

        locations.emplace_back(place, renamedPlace, QGeoCoordinate(latitude,longitude));
    }
}
