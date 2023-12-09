#ifndef DETAILEDWEATHERAPI_H
#define DETAILEDWEATHERAPI_H

#include <QGeoCoordinate>
#include <QThread>
#include <QString>

#include "GeoLocationData.h"
#include "WeatherAPI.h"

class DetailedWeatherData;

class DetailedWeatherAPI : public WeatherAPI
{
    Q_OBJECT
public:
    explicit DetailedWeatherAPI(const GeoLocationData& location, QObject *parent = nullptr);
    ~DetailedWeatherAPI() = default;

private slots:
    void replyFinished(QNetworkReply *reply) override;

protected:
    void run() override;

protected:
    GeoLocationData location;

    void fetchData(const QGeoCoordinate &coordinates);

};

#endif // DETAILEDWEATHERAPI_H

