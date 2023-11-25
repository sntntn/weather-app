#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QGeoCoordinate>
#include <QThread>
#include <QString>

class WeatherData;

class WeatherAPI : public QThread
{
    Q_OBJECT
public:
    explicit WeatherAPI(QString& location, QObject *parent = nullptr);
    ~WeatherAPI();

signals:
    void dataFetched(QSharedPointer<WeatherData> data);

private slots:
    void replyFinished(QNetworkReply* reply);

private:
    QString location;
    QNetworkAccessManager* networkManager;

    void fetchData(const QGeoCoordinate &coordinates);
    QGeoCoordinate locationToCoordinate(const QString &location); // test

protected:
    void run();
};

#endif // WEATHERAPI_H
