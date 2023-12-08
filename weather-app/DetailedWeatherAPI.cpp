#include "DetailedWeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>

#include "WeatherData.h"
#include "DetailedWeatherData.h"
#include "Parser.h"

DetailedWeatherAPI::DetailedWeatherAPI(QString& location, QObject *parent)
    : WeatherAPI{location, parent}
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherAPI::replyFinished);
}

DetailedWeatherAPI::~DetailedWeatherAPI() {}

void DetailedWeatherAPI::run()
{
    QGeoCoordinate coordinates = locationToCoordinate(location);
    fetchData(coordinates);
    exec();
}

QGeoCoordinate DetailedWeatherAPI::locationToCoordinate(const QString &location){ // test
    if(location == "Belgrade"){
        return QGeoCoordinate(44.8125, 20.4375);
        //return QGeoCoordinate(35.6764, 139.6500);  //Tokio

    }
    return QGeoCoordinate(0,0);
}


void DetailedWeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
//    QUrl url("https://api.open-meteo.com/v1/forecast");
//    QUrlQuery query;
    // todo
    QString latitude  = QString::number(coordinates.latitude());
    QString longitude = QString::number(coordinates.longitude());

    QUrl url("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query;
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,weather_code,is_day");
    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min");
    query.addQueryItem("timezone", "auto");
    url.setQuery(query);
    QNetworkRequest request(url);
    networkManager->get(request);

}

void DetailedWeatherAPI::replyFinished(QNetworkReply *reply){

    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << "Error: " << reply->errorString().toStdString() << std::endl;
        return;
    }

    QString jsonData = reply->readAll();
    auto data = Parser::parseDetailedWeatherData(jsonData);

    // Emit the signal with a QSharedPointer pointing to the new Data object
    emit dataFetched(data);

    reply->deleteLater();
}


