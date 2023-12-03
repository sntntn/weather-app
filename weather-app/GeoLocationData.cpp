#include "GeoLocationData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

GeoLocationData::GeoLocationData(QString& location, QString& renamedPlace, QGeoCoordinate& coordinates)
    : place(location)
    , renamedPlace(renamedPlace)
    , coordinates(coordinates)
{

}
