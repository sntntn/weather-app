#ifndef GEOCODINGAPI_H
#define GEOCODINGAPI_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

#include <QObject>
#include "GeoLocationData.h"

class GeocodingAPI : public QObject
{
    Q_OBJECT
public:
    GeocodingAPI();
    ~GeocodingAPI();

    void handleGeocodingResponse(QNetworkReply* reply);

signals:
    void geocodingDataUpdated(const QList<GeoLocationData>& locations);
public slots:
    void geocodeCity(const QString &location);

private:
    void processResultsArray(const QJsonArray& resultsArray, QList<GeoLocationData>& locations);
    QString OPEN_CAGE_API_KEY;
    QNetworkAccessManager* m_networkManager;
};

#endif // GEOCODINGAPI_H
