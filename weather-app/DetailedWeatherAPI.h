#ifndef DETAILEDWEATHERAPI_H
#define DETAILEDWEATHERAPI_H

#include <QGeoCoordinate>
//#include <QThread>
#include <QString>
#include <QNetworkAccessManager>
#include <QObject>

#include "GeoLocationData.h"
//#include "WeatherAPI.h"

class DetailedWeatherData;

class DetailedWeatherAPI : public QObject
{
    Q_OBJECT
public:
    explicit DetailedWeatherAPI(const GeoLocationData& location, QObject *parent = nullptr);
    ~DetailedWeatherAPI() = default;
    void fetchData(const QGeoCoordinate &coordinates);

private slots:
    void replyFinished(QNetworkReply *reply);

//protected:
//    void run() override;

signals:
    void dataFetched(const QSharedPointer<Data> &data);

private:
    GeoLocationData location;
    QNetworkAccessManager* networkManager;

    QSharedPointer<DetailedWeatherData> parseDetailedWeatherData(const QString& jsonData, const GeoLocationData &geoLocation);
};

#endif // DETAILEDWEATHERAPI_H

