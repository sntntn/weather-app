#ifndef GEOLOCATIONDATA_H
#define GEOLOCATIONDATA_H

#include <QGeoCoordinate>

#include "Data.h"

class GeoLocationData : public Data
{
public:
    GeoLocationData() = default;
    ~GeoLocationData() = default;
    GeoLocationData(const GeoLocationData &other) = default;
    GeoLocationData(const QString &place, const QString &renamedPlace, const QGeoCoordinate &coordinates);


    inline QString getPlace() const{
        return m_place;
    }
    inline QString getRenamedPlace() const{
        return m_renamedPlace;
    }
    inline QGeoCoordinate getCoordinates() const{
        return m_coordinates;
    }

    inline void setRenamedPlace(QString renamedPlace){
        m_renamedPlace=renamedPlace;
    }


    GeoLocationData& operator= (const GeoLocationData& other) = default;
    bool operator== (const GeoLocationData &other) const;

private:
    QString m_place;
    QString m_renamedPlace;
    QGeoCoordinate m_coordinates;
};

Q_DECLARE_METATYPE(GeoLocationData)

#endif // GEOLOCATIONDATA_H
