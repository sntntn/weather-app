#ifndef GEOLOCATIONDATA_H
#define GEOLOCATIONDATA_H

#include <QGeoCoordinate>

#include "Data.h"

class GeoLocationData : public Data
{
public:
    GeoLocationData(QString& location, QString& country, QGeoCoordinate& coordinates);

    QString place;
    QString renamedPlace;
    QGeoCoordinate coordinates;
};

#endif // GEOLOCATIONDATA_H
