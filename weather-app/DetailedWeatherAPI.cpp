#include "DetailedWeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>

#include "WeatherData.h"
#include "DetailedWeatherData.h"
#include "ApiHandler.h"
#include "Parser.h"

DetailedWeatherAPI::DetailedWeatherAPI(const GeoLocationData &location, QObject *parent)
    : WeatherAPI{location, parent}
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &DetailedWeatherAPI::replyFinished);
}

void DetailedWeatherAPI::run()
{
    fetchData(location.getCoordinates());
    exec();
}

void DetailedWeatherAPI::fetchData(const QGeoCoordinate &coordinates)
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
    //query.addQueryItem("temperature_unit", Settings::instance().temperatureUnitApiParameter());

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
    auto data = Parser::parseWeatherData(jsonData, location);

    emit dataFetched(data);
    this->quit();

    reply->deleteLater();
}


