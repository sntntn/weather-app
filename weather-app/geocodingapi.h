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

    void geocodeCity(const QString& cityName);
    void handleGeocodingResponse(QNetworkReply* reply);
    void testCityFunction();

private:
    const QString OPEN_CAGE_API_KEY = "0741d020f58441f6b58ae4dc4128740d";  // TODO za config fajl
    QNetworkAccessManager* m_networkManager;
};

#endif // GEOCODINGAPI_H
