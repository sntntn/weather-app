#ifndef LOCATION_H
#define LOCATION_H

#include "qgeopositioninfosource.h"
#include "qobject.h"

class Location : public QObject
{
    Q_OBJECT
public:
    Location(QObject *parent = 0);
private slots:
    void positionUpdated(const QGeoPositionInfo &info);
};

#endif // LOCATION_H
