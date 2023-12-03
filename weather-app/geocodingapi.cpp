#include "geocodingapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>

GeocodingAPI::GeocodingAPI()
    :m_networkManager(new QNetworkAccessManager(this))
{
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &GeocodingAPI::handleGeocodingResponse);
}
GeocodingAPI::~GeocodingAPI()
{
    delete m_networkManager;
}

void GeocodingAPI::geocodeCity(const QString& cityName) {

    QString apiUrl = QString("https://api.opencagedata.com/geocode/v1/json?q=%1&key=%2")
                         .arg(cityName)
                         .arg(OPEN_CAGE_API_KEY);

    QNetworkRequest request{QUrl(apiUrl)};
    m_networkManager->get(request);
}

void GeocodingAPI::handleGeocodingResponse(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

    if (!jsonResponse.isObject()) {
        qDebug() << "Error: Invalid JSON response";
        return;
    }

    QJsonObject jsonObject = jsonResponse.object();
    if (!jsonObject.contains("results") || !jsonObject["results"].isArray()) {
        qDebug() << "Error: Missing or invalid 'results' array in JSON response";
        return;
    }

    QJsonArray resultsArray = jsonObject["results"].toArray();
    if (resultsArray.isEmpty()) {
        qDebug() << "Error: Empty 'results' array in JSON response";
        return;
    }

    // json za https://api.opencagedata.com/geocode/v1/json?q=Be&key=0741d020f58441f6b58ae4dc4128740d       formatted

    QList<GeoLocationData> locations;
    for (const QJsonValue& resultValue : resultsArray) {
        QJsonObject resultObject = resultValue.toObject();

        if (!resultObject.contains("formatted") || !resultObject["formatted"].isString()) {
            qDebug() << "Error: Missing or invalid 'formatted' string in JSON response";
            continue;  // Preskoči ovaj rezultat i idi na sledeći
        }

        QString place = resultObject["formatted"].toString();
        if(!place.isEmpty() && place.at(0).isDigit()){
            continue;       //preskacemo postanske brojeve  -> prikazuje opstine
        }

        if (!resultObject.contains("geometry") || !resultObject["geometry"].isObject()) {
            qDebug() << "Error: Missing or invalid 'geometry' object in JSON response";
            continue;
        }

        QJsonObject geometryObject = resultObject["geometry"].toObject();
        if (!geometryObject.contains("lat") || !geometryObject.contains("lng")) {
            qDebug() << "Error: Missing 'lat' or 'lng' in 'geometry' object";
            continue;
        }

        double latitude = geometryObject["lat"].toDouble();
        double longitude = geometryObject["lng"].toDouble();

        QString renamedPlace;
        int commaIndex=place.indexOf(',');
        if(commaIndex !=-1 ){
            renamedPlace=place.left(commaIndex).trimmed();
        }
        else{
            renamedPlace=place;
        }

        GeoLocationData gld{place, renamedPlace, QGeoCoordinate(latitude,longitude)};
        locations.append(gld);
    }
    emit geocodingDataUpdated(locations);
    reply->deleteLater();
}

//Test
//Bern          Latitude: 46.9485 Longitude: 7.45217
//Belgrade      Latitude: 44.8178 Longitude: 20.4569
void GeocodingAPI::testCityFunction(const QString &location) {
    geocodeCity(location);
}
