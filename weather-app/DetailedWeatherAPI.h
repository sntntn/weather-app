#ifndef DETAILEDWEATHERAPI_H
#define DETAILEDWEATHERAPI_H

#include "WeatherAPI.h"

class DetailedWeatherAPI : public WeatherAPI
{
public:
    explicit DetailedWeatherAPI(QString& location, QObject *parent = nullptr);
    ~DetailedWeatherAPI();

private slots:
    void replyFinished(QNetworkReply *reply) override;

private:
    void fetchData(const QGeoCoordinate &coordinates);
};

#endif // DETAILEDWEATHERAPI_H
