#include "UserLocation.h"

#include "GeoLocationData.h"
#include "Settings.h"

UserLocation::UserLocation(QObject *parent)
    : QObject{parent}
    , source(QGeoPositionInfoSource::createDefaultSource(this))
{
    if(source != nullptr){
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &UserLocation::positionUpdated);
        connect(source, &QGeoPositionInfoSource::errorOccurred, this, &UserLocation::handleError);
    }
}

void UserLocation::getLocation()
{
    source->requestUpdate();
}

void UserLocation::positionUpdated(const QGeoPositionInfo &info)
{
    GeoLocationData data = GeoLocationData("My location", "My location", info.coordinate(), "");
    emit userLocationFetched(data);
}

void UserLocation::handleError(const QGeoPositionInfoSource::Error)
{
    emit userLocationError(errMsg);
}
