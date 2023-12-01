#include "DetailedWeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>

#include "Parser.h"

DetailedWeatherAPI::DetailedWeatherAPI(QString& location, QObject *parent)
    : WeatherAPI{location, parent}
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherAPI::replyFinished);
}

DetailedWeatherAPI::~DetailedWeatherAPI() {}

void DetailedWeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
//    QUrl url("https://api.open-meteo.com/v1/forecast");
//    QUrlQuery query;
    // todo
}

void DetailedWeatherAPI::replyFinished(QNetworkReply *reply){
//    if (reply->error() != QNetworkReply::NoError) {
//        std::cerr << "Error: " << reply->errorString().toStdString() << std::endl;
//        return; // TODO
//    }

//    QString jsonData = reply->readAll();
//    auto data = Parser::parseDetailedWeatherData(jsonData);
//    emit dataFetched(data);

//    reply->deleteLater();
}
