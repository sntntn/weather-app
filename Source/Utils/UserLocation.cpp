#include "UserLocation.h"

#include "GeoLocationData.h"
#include "Settings.h"

UserLocation::UserLocation(QObject *parent)
    : QObject{parent}
    , source(QGeoPositionInfoSource::createDefaultSource(this))
{
    if(source != nullptr){
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &UserLocation::positionUpdated);
    }
}

void UserLocation::getLocation()
{
    source->requestUpdate();
}

void UserLocation::positionUpdated(const QGeoPositionInfo &info)
{
    // todo konstruktor geolocation
    GeoLocationData data = GeoLocationData("My location", "My location", info.coordinate());
    emit userLocationFetched(data);
}
