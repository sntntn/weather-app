#include "WeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>

#include "WeatherData.h"
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
    auto data = Parser::parseWeatherData(jsonData, location);

    emit dataFetched(data);
    this->quit();

    reply->deleteLater();
}
