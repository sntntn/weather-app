#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QGeoCoordinate>
#include <QString>

#include "ApiHandler.h"
#include "GeoLocationData.h"

class WeatherData;
class GeoLocationData;

class WeatherAPI : public ApiHandler
{
    Q_OBJECT

public:
    explicit WeatherAPI(QObject *parent = nullptr);
    ~WeatherAPI() = default;
    void fetchData(const GeoLocationData &location);

public slots:
    void replyFinished(QNetworkReply* reply) override;

private:
    QSharedPointer<WeatherData> parseWeatherData(const QString& jsonData, const GeoLocationData &geoLocation);
};

#endif // WEATHERAPI_H
