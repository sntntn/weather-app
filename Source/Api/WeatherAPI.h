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

signals:
    void dataFetched(const QSharedPointer<Data> &data);
    void errorOccured(const QString &errMsg);

public slots:
    void replyFinished(QNetworkReply* reply) override;

private:
    const QString errMsg = "Error occured while fetching weather data. "
                           "Please check your internet connection.";
};

#endif // WEATHERAPI_H
