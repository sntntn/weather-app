#include "DetailedWeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QDebug>

#include "DetailedWeatherData.h"
#include "ApiHandler.h"
#include "Parser.h"
#include "Settings.h"

DetailedWeatherAPI::DetailedWeatherAPI(const GeoLocationData &location, QObject *parent)
    : QObject(parent)
    , location(location)
    , networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &DetailedWeatherAPI::replyFinished);
}

//void DetailedWeatherAPI::run()
//{
//    fetchData(location.getCoordinates());
//    exec();
//}

void DetailedWeatherAPI::fetchData(const QGeoCoordinate &coordinates)
{
    QString latitude  = QString::number(coordinates.latitude());
    QString longitude = QString::number(coordinates.longitude());

    QUrl url("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query;
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,weather_code,is_day,wind_speed_10m,apparent_temperature,precipitation,relative_humidity_2m,visibility,pressure_msl");
    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min,uv_index_max");
    query.addQueryItem("timezone", "auto");

    query.addQueryItem("hourly", "temperature_2m");  // Include hourly temperature forecast
    // Add the next 24 hours as the forecast duration
    QDateTime now = QDateTime::currentDateTime();
    QDateTime next24Hours = now.addSecs(24 * 60 * 60); // Add 24 hours
    query.addQueryItem("start", now.toString(Qt::ISODate));
    query.addQueryItem("end", next24Hours.toString(Qt::ISODate));

    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min");  // Include daily temperature forecast for max and min
    //Add the next 7 days as the forecast duration
    QDateTime next7Days = now.addDays(7); // Add 7 days
    query.addQueryItem("start", now.toString(Qt::ISODate));
    query.addQueryItem("end", next7Days.toString(Qt::ISODate));

    query.addQueryItem("temperature_unit", Settings::instance().temperatureUnitApiParameter());


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
    //this->quit();

    reply->deleteLater();
}

