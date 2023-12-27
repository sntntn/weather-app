#include "DetailedWeatherAPI.h"

#include <iostream>
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QDebug>
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
    query.addQueryItem("current", "temperature_2m,weather_code,is_day,wind_speed_10m,apparent_temperature,precipitation,relative_humidity_2m,visibility,pressure_msl,uv_index,precipitation_probability,wind_direction_10m,wind_gusts_10m");
    query.addQueryItem("daily", "temperature_2m_max,temperature_2m_min,weather_code,sunrise,sunset");
    query.addQueryItem("timezone", "auto");

    query.addQueryItem("hourly", "temperature_2m,weather_code,is_day");

    QDateTime now = QDateTime::currentDateTime();
    QDateTime next24Hours = now.addSecs(24 * 60 * 60); // Add 24 hours
    query.addQueryItem("start", now.toString(Qt::ISODate));
    query.addQueryItem("end", next24Hours.toString(Qt::ISODate));

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
    auto data = parseDetailedWeatherData(jsonData, location);

    emit dataFetched(data);
    //this->quit();

    reply->deleteLater();
}

QSharedPointer<DetailedWeatherData> DetailedWeatherAPI::parseDetailedWeatherData(const QString& jsonData, const GeoLocationData &geoLocation)
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
    int precipitation = static_cast<int>(qRound(current.value("precipitation").toDouble()));
    int humidity = static_cast<int>(qRound(current.value("relative_humidity_2m").toDouble()));
    int visibility = static_cast<int>(qRound(current.value("visibility").toDouble()));
    int pressure =  static_cast<int>(qRound(current.value("pressure_msl").toDouble()));
    int uvIndex = static_cast<int>(qRound(current.value("uv_index").toDouble()));
    int precipitationProbability = static_cast<int>(qRound(current.value("precipitation_probability").toDouble()));
    int windDirection = static_cast<int>(qRound(current.value("wind_direction_10m").toDouble()));
    int windGusts = static_cast<int>(qRound(current.value("wind_gusts_10m").toDouble()));

    qDebug() << "temperature:" << temperature;
    qDebug() << "weatherCode:" << weatherCode;
    qDebug() << "isDay:" << isDay;
    qDebug() << "wind speed:" << windSpeed;
    qDebug() << "real feel:" << apparentTemperature;
    qDebug() << "precipitation:" << precipitation;
    qDebug() << "humidity:" << humidity;
    qDebug() << "visibility:" << visibility;
    qDebug() << "pressure:" << pressure;
    qDebug() << "uv:" << uvIndex;
    qDebug() << "precipitation probability:" << precipitationProbability;
    qDebug() << "wind direction:" << windDirection;
    qDebug() << "wind gusts:" << windGusts;

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
        if (formattedCurrentTime <= timeEntry) {
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

    qDebug() << ht;
    qDebug() << hc;
    qDebug() << hd;
    qDebug() << "TimeStamps: " << hts;

    //TODO: weather_code, sunrise i sunset odraditi za narednih 7 dana
    QJsonArray weeklyCodeJ = daily.value("weather_code").toArray();
    QJsonArray weeklySunriseJ = daily.value("sunrise").toArray();
    QJsonArray weeklySunsetJ = daily.value("sunset").toArray();
    QJsonArray weeklyDayJ = daily.value("time").toArray();

    QVector<int> weeklyCode;
    QVector<QString> weeklySunrise;
    QVector<QString> weeklySunset;
    QVector<QString> weeklyDayName;
    for (int i = 0; i < 7; i++){
        int wc = static_cast<int>(qRound(weeklyCodeJ[i].toDouble()));
        weeklyCode.push_back(wc);

        QString dailySunrise = static_cast<QString>(weeklySunriseJ[i].toString());
        weeklySunrise.push_back(dailySunrise.mid(11,5));

        QString dailySunset = static_cast<QString>(weeklySunsetJ[i].toString());
        weeklySunset.push_back(dailySunset.mid(11,5));

        QDate date = QDate::fromString(static_cast<QString>(weeklyDayJ[i].toString()), "yyyy-MM-dd");
        QString dayName = date.toString("dddd");
        weeklyDayName.push_back(dayName);
    }

    qDebug() << "weekly code:" << weeklyCode;
    qDebug() << "weekly sunrise:" << weeklySunrise;
    qDebug() << "weekly sunset:" << weeklySunset;
    qDebug() << "weekly day:" << weeklyDayName;

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

    qDebug() << weeklyMaxTemp;
    qDebug() << weeklyMinTemp;

    QSharedPointer<DetailedWeatherData> data(new DetailedWeatherData(geoLocation,
                                                                     temperature,
                                                                     weatherCode,
                                                                     isDay,
                                                                     timeZone,
                                                                     windSpeed,
                                                                     windGusts,
                                                                     windDirection,
                                                                     apparentTemperature,
                                                                     precipitation,
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
                                                                     weeklySunrise,
                                                                     weeklySunset,
                                                                     weeklyDayName));



    return data;
}
