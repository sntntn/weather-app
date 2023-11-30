#ifndef GEOCODINGAPI_H
#define GEOCODINGAPI_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

#include <QObject>

class GeocodingAPI : public QObject
{
    Q_OBJECT
public:
    GeocodingAPI();
    ~GeocodingAPI();

    void geocodeCity(const QString& cityName);
    void handleGeocodingResponse(QNetworkReply* reply);

    inline double getLatitude(){
        return m_latitude;
    }
    inline double getLongitude(){
        return m_longitude;
    }
    inline QString getPlace(){
        return m_place;
    }

signals:
    void geocodingDataUpdated(const QString& place, double latitude, double longitude);
public slots:
    void testCityFunction(const QString &location);

private:
    const QString OPEN_CAGE_API_KEY = "0741d020f58441f6b58ae4dc4128740d";  // TODO za config fajl
    QNetworkAccessManager* m_networkManager;

    double m_latitude;
    double m_longitude;
    QString m_place;
};

#endif // GEOCODINGAPI_H
