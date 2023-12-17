#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QGeoCoordinate>
#include <QThread>
#include <QString>

#include "ApiHandler.h"
#include "GeoLocationData.h"

class WeatherData;
class GeoLocationData;

class WeatherAPI : public ApiHandler
{
    Q_OBJECT
public:
    explicit WeatherAPI(const GeoLocationData& location, QObject *parent = nullptr);
    ~WeatherAPI() = default;

public slots:
    void replyFinished(QNetworkReply* reply) override;

protected:
    GeoLocationData location;

    void run() override;
    void fetchData(const QGeoCoordinate &coordinates);
};

#endif // WEATHERAPI_H
