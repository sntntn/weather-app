#include "GeoLocationData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>
#include <QVariantMap>
#include <QVariantList>

GeoLocationData::GeoLocationData(const QString &place, const QString &renamedPlace, const QGeoCoordinate &coordinates)
    : m_place(place)
    , m_renamedPlace(renamedPlace)
    , m_coordinates(coordinates)
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
    map.insert("coordinates", QVariant::fromValue(m_coordinates));

    return map;
}
void GeoLocationData::fromVariant(const QVariant & variant){

    const auto map = variant.toMap();
    m_place = map.value("place").toString();
    m_renamedPlace = map.value("renamedPlace").toString();
    m_coordinates = map.value("coordinates").value<QGeoCoordinate>();
}

