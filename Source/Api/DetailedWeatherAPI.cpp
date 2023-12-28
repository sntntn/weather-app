#include "DetailedWeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDate>

#include "DetailedWeatherData.h"
#include "ApiHandler.h"
#include "Parser.h"
#include "Settings.h"

DetailedWeatherAPI::DetailedWeatherAPI(const GeoLocationData &location, QObject *parent)
    : ApiHandler(parent)
    , location(location)
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &DetailedWeatherAPI::replyFinished);
}

void DetailedWeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
    QString latitude  = QString::number(coordinates.latitude());
    QString longitude = QString::number(coordinates.longitude());

    QUrl url("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query;
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,weather_code,is_day,wind_speed_10m,apparent_temperature,snow_depth,relative_humidity_2m,visibility,pressure_msl,uv_index,wind_direction_10m,wind_gusts_10m");
    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min,weather_code,sunrise,sunset,precipitation_sum");
    query.addQueryItem("timezone", "auto");

    query.addQueryItem("hourly", "temperature_2m,weather_code,is_day,precipitation");

    query.addQueryItem("temperature_unit", Settings::instance().temperatureUnitApiParameter());
    query.addQueryItem("wind_speed_unit", Settings::instance().windSpeedUnitApiParameter());
    query.addQueryItem("precipitation_unit", Settings::instance().precipitationUnitApiParameter());

    url.setQuery(query);
    QNetworkRequest request(url);
    networkManager->get(request);
}

void DetailedWeatherAPI::replyFinished(QNetworkReply *reply){
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error: " << reply->errorString().toStdString() << std::endl;
        return; // TODO
    }

    QString jsonData = reply->readAll();
    auto data = Parser::parseDetailedWeatherData(jsonData, location);

    emit dataFetched(data);
    reply->deleteLater();
}
