#include "UserLocation.h"
#include "GeoLocationData.h"

UserLocation::UserLocation(QObject *parent)
    : QObject{parent}
    , source(QGeoPositionInfoSource::createDefaultSource(this))
{
    if(source){
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &UserLocation::positionUpdated);
        source->requestUpdate();
    }
}

void UserLocation::positionUpdated(const QGeoPositionInfo &info)
{
    QSharedPointer<GeoLocationData> data(new GeoLocationData("Current location", "", info.coordinate()));
    emit userLocationFetched(data);
}
