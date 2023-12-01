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
    ~WeatherAPI();

private slots:
    void replyFinished(QNetworkReply* reply) override;

private:
    QString location;

    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(const QString &location); // test

protected:
    void run() override;
};

#endif // WEATHERAPI_H
