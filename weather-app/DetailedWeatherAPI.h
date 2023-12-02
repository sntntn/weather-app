#ifndef DETAILEDWEATHERAPI_H
#define DETAILEDWEATHERAPI_H

#include "WeatherAPI.h"

class DetailedWeatherData;

class DetailedWeatherAPI : public WeatherAPI
{
public:
    explicit DetailedWeatherAPI(QString& location, QObject *parent = nullptr);
    ~DetailedWeatherAPI();

private slots:
    void replyFinished(QNetworkReply *reply) override;

protected:
    void run() override;

protected:
    QString location;

    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(const QString &location);

};

#endif // DETAILEDWEATHERAPI_H
