#ifndef WEATHERAPI_H
#define WEATHERAPI_H

class WeatherData;
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QGeoCoordinate>

#include "geocodingapi.h"

class WeatherAPI : public QObject
{
    Q_OBJECT
public:
    explicit WeatherAPI(QObject *parent = nullptr);
    ~WeatherAPI();
    void fetchData(const QString &location);

signals:
    void dataFetched(WeatherData *data);

private slots:
    void replyFinished(QNetworkReply* reply);
    void updateGeocodingData(const QString& place, double latitude, double longitude);

private:
    QNetworkAccessManager* networkManager;
    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(const QString &location); // test

    GeocodingAPI geocodingApi;
};

#endif // WEATHERAPI_H
