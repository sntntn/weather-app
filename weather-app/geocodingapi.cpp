#include "geocodingapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


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

    // aj da kazemo da zelimo prvi rezultat za pocetak                  #TO DO kasnije, za druge opcije -> autokomplit
    // json za https://api.opencagedata.com/geocode/v1/json?q=Be&key=0741d020f58441f6b58ae4dc4128740d       formatted
    QJsonObject firstResult = resultsArray.first().toObject();

    if (!firstResult.contains("formatted") || !firstResult["formatted"].isString()) {
        qDebug() << "Error: Missing or invalid 'formatted' string in JSON response";
        return;
    }

    m_place = firstResult["formatted"].toString();

    if (!firstResult.contains("geometry") || !firstResult["geometry"].isObject()) {
        qDebug() << "Error: Missing or invalid 'geometry' object in JSON response";
        return;
    }

    QJsonObject geometryObject = firstResult["geometry"].toObject();
    if (!geometryObject.contains("lat") || !geometryObject.contains("lng")) {
        qDebug() << "Error: Missing 'lat' or 'lng' in 'geometry' object";
        return;
    }

    m_latitude = geometryObject["lat"].toDouble();
    m_longitude = geometryObject["lng"].toDouble();
    //emit geocodingDataUpdated(m_place,m_latitude,m_longitude);
    qDebug() << "-----> City:" << m_place << "Latitude:" << m_latitude << "Longitude:" << m_longitude;

    reply->deleteLater();
}

//Test
//Bern          Latitude: 46.9485 Longitude: 7.45217
//Belgrade      Latitude: 44.8178 Longitude: 20.4569
void GeocodingAPI::testCityFunction(const QString &location) {
    geocodeCity(location);
}
