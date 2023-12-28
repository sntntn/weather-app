#include "Parser.h"

#include "WeatherData.h"
#include "DetailedWeatherData.h"
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
    int rain = static_cast<int>(qRound(current.value("rain").toDouble()));
    int snow = static_cast<int>(qRound(current.value("snowfall").toDouble()));
    int humidity = static_cast<int>(qRound(current.value("relative_humidity_2m").toDouble()));
    int visibility = static_cast<int>(qRound(current.value("visibility").toDouble()));
    int pressure =  static_cast<int>(qRound(current.value("pressure_msl").toDouble()));
    int uvIndex = static_cast<int>(qRound(current.value("uv_index").toDouble()));
    int windDirection = static_cast<int>(qRound(current.value("wind_direction_10m").toDouble()));
    int windGusts = static_cast<int>(qRound(current.value("wind_gusts_10m").toDouble()));

    QJsonArray hourlyTimeJ = hourly.value("time").toArray();
    QJsonArray hourlyTempJ = hourly.value("temperature_2m").toArray();
    QJsonArray hourlyCodeJ = hourly.value("weather_code").toArray();
    QJsonArray hourlyIsDayJ = hourly.value("is_day").toArray();

    QDateTime currentTime = QDateTime::currentDateTime().toTimeZone(timeZone);
    QString formattedCurrentTime = currentTime.toString(Qt::ISODate).left(16);

    int matchingIndex = -1;
    const int hourlyTimeJsize = hourlyTimeJ.size();

    for (int i = 0; i < hourlyTimeJsize; ++i) {
        QString timeEntry = hourlyTimeJ[i].toString();
        if (formattedCurrentTime < timeEntry) {
            matchingIndex = i - 1;
            break;
        }
    }

    QVector<int> ht;
    QVector<int> hc;
    QVector<bool> hd;
    QVector<QString> hts;

    for (int i = matchingIndex, end = matchingIndex + 24; i < end; i++){
        int temperature = static_cast<int>(qRound(hourlyTempJ[i].toDouble()));
        ht.push_back(temperature);
        int code = hourlyCodeJ[i].toInt();
        hc.push_back(code);
        bool day = static_cast<bool>(hourlyIsDayJ[i].toInt());
        hd.push_back(day);
        QString time = hourlyTimeJ[i].toString();
        hts.push_back(time.mid(11, 5));
    }

    //TODO: weather_code, sunrise i sunset odraditi za narednih 7 dana
    QJsonArray weeklyCodeJ = daily.value("weather_code").toArray();
    QJsonArray weeklySunriseJ = daily.value("sunrise").toArray();
    QJsonArray weeklySunsetJ = daily.value("sunset").toArray();
    QJsonArray weeklyDayJ = daily.value("time").toArray();

    QVector<int> weeklyCode;
    QVector<QString> weeklyDayName;


    for (int i = 0; i < 7; i++){
        int wc = static_cast<int>(qRound(weeklyCodeJ[i].toDouble()));
        weeklyCode.push_back(wc);

        QDate date = QDate::fromString(static_cast<QString>(weeklyDayJ[i].toString()), "yyyy-MM-dd");
        QString dayName = date.toString("dddd");
        weeklyDayName.push_back(dayName);
    }

    QString sunrise = static_cast<QString>(weeklySunriseJ[0].toString());
    QString sunset = static_cast<QString>(weeklySunsetJ[0].toString());

    QJsonArray weeklyMaxTempJ = daily.value("temperature_2m_max").toArray();
    QVector<int> weeklyMaxTemp;
    for (int i = 0; i < 7; i++){
        int temperature = static_cast<int>(qRound(weeklyMaxTempJ[i].toDouble()));
        weeklyMaxTemp.push_back(temperature);
    }
    QJsonArray weeklyMinTempJ = daily.value("temperature_2m_min").toArray();
    QVector<int> weeklyMinTemp;
    for (int i = 0; i < 7; i++){
        int temperature = static_cast<int>(qRound(weeklyMinTempJ[i].toDouble()));
        weeklyMinTemp.push_back(temperature);
    }

    QSharedPointer<DetailedWeatherData> data(new DetailedWeatherData(geoLocation,
                                                                     temperature,
                                                                     weatherCode,
                                                                     isDay,
                                                                     timeZone,
                                                                     windSpeed,
                                                                     windGusts,
                                                                     windDirection,
                                                                     apparentTemperature,
                                                                     rain,
                                                                     snow,
                                                                     uvIndex,
                                                                     humidity,
                                                                     visibility,
                                                                     pressure,
                                                                     ht,
                                                                     hc,
                                                                     hd,
                                                                     hts,
                                                                     weeklyMaxTemp,
                                                                     weeklyMinTemp,
                                                                     weeklyCode,
                                                                     sunrise,
                                                                     sunset,
                                                                     weeklyDayName));
    return data;
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

        QString country = "";
        if(resultObject.contains("components") && resultObject["components"].isObject()){
            QJsonObject componentsObject = resultObject["components"].toObject();
            if(componentsObject.contains("country") && componentsObject["country"].isString()){
                country = componentsObject["country"].toString();
            }
        }

        QString renamedPlace;
        auto commaIndex=place.indexOf(',');
        commaIndex == -1 ? renamedPlace = place : renamedPlace = place.left(commaIndex).trimmed();

        locations.emplace_back(place, renamedPlace, QGeoCoordinate(latitude,longitude),country);
    }
}

