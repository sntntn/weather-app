#include "GeoLocationData.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

GeoLocationData::GeoLocationData(const QString place, QString renamedPlace,const QGeoCoordinate coordinates)
    : m_place(place)
    , m_renamedPlace(renamedPlace)
    , m_coordinates(coordinates)
{}

bool GeoLocationData::operator==(const GeoLocationData &other) const
{
    return this->m_coordinates == other.m_coordinates;
}
