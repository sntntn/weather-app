#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QGeoCoordinate>
#include <QThread>
#include <QString>

#include "ApiHandler.h"

class WeatherData;

class WeatherAPI : public ApiHandler
{
    Q_OBJECT
public:
    explicit WeatherAPI(QString& location, QObject *parent = nullptr);
    ~WeatherAPI() = default;

public slots:
    void replyFinished(QNetworkReply* reply) override;

protected:
    void run() override;

protected:
    QString location;

    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(const QString &location); // test
};

#endif // WEATHERAPI_H
