#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QGeoCoordinate>
#include <QThread>
#include <QString>

#include "ApiHandler.h"
#include "GeoLocationData.h"

class WeatherData;

class WeatherAPI : public ApiHandler
{
    Q_OBJECT
public:
    explicit WeatherAPI(const GeoLocationData& location, QObject *parent = nullptr);
    ~WeatherAPI() = default;

public slots:
    void replyFinished(QNetworkReply* reply) override;

protected:
    void run() override;

protected:
    GeoLocationData location;

    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(GeoLocationData& location); // test
};

#endif // WEATHERAPI_H
