#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include "WeatherData.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QGeoCoordinate>

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

private:
    QNetworkAccessManager* networkManager;
    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(const QString &location); // test
};

#endif // WEATHERAPI_H
