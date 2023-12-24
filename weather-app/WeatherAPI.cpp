#include "WeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "WeatherData.h"
#include "GeoLocationData.h"
#include "Parser.h"
#include "Settings.h"

WeatherAPI::WeatherAPI(const GeoLocationData &location, QObject *parent)
    : ApiHandler{parent}
    , location(location)
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherAPI::replyFinished);
//    networkManager->moveToThread(this);   // TODO?
}

void WeatherAPI::run()
{
    fetchData(location.getCoordinates());
    exec();
}

void WeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
    QString latitude  = QString::number(coordinates.latitude());
    QString longitude = QString::number(coordinates.longitude());

    QUrl url("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query;
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,weather_code,is_day");
    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min");
    query.addQueryItem("timezone", "auto");
    query.addQueryItem("temperature_unit", Settings::instance().temperatureUnitApiParameter());

    url.setQuery(query);
    QNetworkRequest request(url);
    networkManager->get(request);
}

void WeatherAPI::replyFinished(QNetworkReply *reply){
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error: " << reply->errorString().toStdString() << std::endl;
        return; // TODO
    }

    QString jsonData = reply->readAll();
    auto data = parseWeatherData(jsonData, location);

    emit dataFetched(data);
    this->quit();

    reply->deleteLater();
}

QSharedPointer<WeatherData> WeatherAPI::parseWeatherData(const QString& jsonData, const GeoLocationData &geoLocation)
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
