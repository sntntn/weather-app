#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include "ApiHandler.h"

#include <QGeoCoordinate>
#include <QString>

#include "GeoLocationData.h"

class WeatherData;
class GeoLocationData;

class WeatherAPI : public ApiHandler
{
  Q_OBJECT

public:
  explicit WeatherAPI(QObject *parent = nullptr);
  ~WeatherAPI() override = default;
  void fetchData(const GeoLocationData &location);

signals:
    void dataFetched(QSharedPointer<WeatherData> data);

public slots:
  void replyFinished(QNetworkReply *reply) override;
};

#endif // WEATHERAPI_H
