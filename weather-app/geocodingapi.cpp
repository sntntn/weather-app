// geocodingapi.cpp
#include "geocodingapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

GeocodingAPI::GeocodingAPI() {
}

void GeocodingAPI::geocodeCity(const QString& cityName) {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &GeocodingAPI::handleGeocodingResponse);

    QString apiUrl = QString("https://api.opencagedata.com/geocode/v1/json?q=%1&key=%2")
                         .arg(cityName)
                         .arg(OPEN_CAGE_API_KEY);

    QNetworkRequest request{QUrl(apiUrl)};
    manager->get(request);
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

    // aj da kazemo da zelimo prvi rezultat za pocetak                  #TO DO kasnije, za druge opcije -> autokomplit
    QJsonObject firstResult = resultsArray.first().toObject();

    if (!firstResult.contains("formatted") || !firstResult["formatted"].isString()) {
        qDebug() << "Error: Missing or invalid 'formatted' string in JSON response";
        return;
    }

    QString formattedAddress = firstResult["formatted"].toString();

    if (!firstResult.contains("geometry") || !firstResult["geometry"].isObject()) {
        qDebug() << "Error: Missing or invalid 'geometry' object in JSON response";
        return;
    }

    QJsonObject geometryObject = firstResult["geometry"].toObject();
    if (!geometryObject.contains("lat") || !geometryObject.contains("lng")) {
        qDebug() << "Error: Missing 'lat' or 'lng' in 'geometry' object";
        return;
    }

    double latitude = geometryObject["lat"].toDouble();
    double longitude = geometryObject["lng"].toDouble();

    qDebug() << "City:" << formattedAddress << "Latitude:" << latitude << "Longitude:" << longitude;

    reply->deleteLater();
}

//Test
//Bern          Latitude: 46.9485 Longitude: 7.45217
//Belgrade      Latitude: 44.8178 Longitude: 20.4569
void GeocodingAPI::testCityFunction() {
    QString cityName = "Belgrade";
    geocodeCity(cityName);
}
