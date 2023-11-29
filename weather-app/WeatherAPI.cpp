#include "WeatherAPI.h"
#include "WeatherData.h"
#include "Parser.h"
#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>

WeatherAPI::WeatherAPI(QObject *parent)
    : QObject{parent},
    networkManager(new QNetworkAccessManager(this))
{
    connect(&geocodingApi, &GeocodingAPI::geocodingDataUpdated, this, &WeatherAPI::updateGeocodingData);
    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherAPI::replyFinished);
}

WeatherAPI::~WeatherAPI()
{
    delete networkManager;
}

QGeoCoordinate WeatherAPI::locationToCoordinate(const QString &location){ // test
    geocodingApi.testCityFunction();


    qDebug()<<"------------";

    if(location == "Belgrade"){
        return QGeoCoordinate(44.8125, 20.4375);
        return QGeoCoordinate(m_lastLatitude, m_lastLongitude);
    }
    return QGeoCoordinate(0,0);
}

void WeatherAPI::fetchData(const QString &location) // test
{
    QGeoCoordinate coordinates = locationToCoordinate(location);
    fetchData(coordinates);
}


void WeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
    QString latitude  = QString::number(coordinates.latitude());
    QString longitude = QString::number(coordinates.longitude());

    QUrl url("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query;
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,rain,wind_speed_10m");
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
    Parser parser;
    WeatherData* data = parser.parseWeatherData(jsonData);
    emit dataFetched(data);

    reply->deleteLater();
}

void WeatherAPI::updateGeocodingData(const QString &place, double latitude, double longitude){
    qDebug() << "--->" << "City:" << geocodingApi.getPlace() << "Latitude:" << geocodingApi.getLatitude() << "Longitude:" << geocodingApi.getLongitude();
    m_lastPlace=place;
    m_lastLatitude=latitude;
    m_lastLongitude=longitude;
}



