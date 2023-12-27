#include "GeoLocationData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>
#include <QVariantMap>
#include <QVariantList>

GeoLocationData::GeoLocationData(QString place, QString renamedPlace, QGeoCoordinate coordinates)
    : m_place(std::move(place))
    , m_renamedPlace(std::move(renamedPlace))
    , m_coordinates(std::move(coordinates))
{
    qRegisterMetaType<GeoLocationData>("GeoLocationData");
}

bool GeoLocationData::operator==(const GeoLocationData &other) const
{
    return this->m_coordinates == other.m_coordinates;
}

QVariant GeoLocationData::toVariant() const{
    QVariantMap map;
    map.insert("place", m_place);
    map.insert("renamedPlace", m_renamedPlace);
    map.insert("latitude", m_coordinates.latitude());
    map.insert("longitude", m_coordinates.longitude());

    return map;
}
void GeoLocationData::fromVariant(const QVariant & variant){

    const auto map = variant.toMap();
    m_place = map.value("place").toString();
    m_renamedPlace = map.value("renamedPlace").toString();
    auto latitude = map.value("latitude").toDouble();
    auto longitude = map.value("longitude").toDouble();
    m_coordinates = QGeoCoordinate(latitude, longitude);
}

GeoLocationData GeoLocationData::fromVariantMap(const QVariantMap& geoLocation)
{
    return GeoLocationData{geoLocation.value("place").toString(),
                           geoLocation.value("renamedPlace").toString(),
                           QGeoCoordinate(geoLocation.value("latitude").toDouble(),
                                          geoLocation.value("longitude").toDouble())};
}

