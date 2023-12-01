#ifndef GEOLOCATIONDATA_H
#define GEOLOCATIONDATA_H

#include <QGeoCoordinate>

#include "Data.h"

class GeoLocationData : public Data
{
public:
    GeoLocationData(QString location, QString country, QGeoCoordinate coordinates);

    QString location;
    QString country;
    QGeoCoordinate coordinates;
};

#endif // GEOLOCATIONDATA_H
