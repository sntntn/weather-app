#include "GeoLocationData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

GeoLocationData::GeoLocationData(QString location, QString country, QGeoCoordinate coordinates)
    : location(location)
    , country(country)
    , coordinates(coordinates)
{

}

