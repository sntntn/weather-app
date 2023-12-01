#include "WeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>

#include "WeatherData.h"
#include "Parser.h"

WeatherAPI::WeatherAPI(QString& location_, QObject *parent)
    : ApiHandler{parent}
    , location(location_)
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherAPI::replyFinished);
//    networkManager->moveToThread(this);   // TODO?
}

WeatherAPI::~WeatherAPI() { }

void WeatherAPI::run()
{
    QGeoCoordinate coordinates = locationToCoordinate(location);
    fetchData(coordinates);
    exec();
}

QGeoCoordinate WeatherAPI::locationToCoordinate(const QString &location){ // test
    if(location == "Belgrade"){
        return QGeoCoordinate(44.8125, 20.4375);
    }
    return QGeoCoordinate(0,0);
}

void WeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
    QString latitude  = QString::number(coordinates.latitude());
    QString longitude = QString::number(coordinates.longitude());

    QUrl url("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query;
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,weather_code");
    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min");
    query.addQueryItem("timezone", "auto");
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
    auto data = Parser::parseWeatherData(jsonData);
    emit dataFetched(data);

    reply->deleteLater();
}
