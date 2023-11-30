#include "location.h"

Location::Location(QObject* parent)
    : QObject{parent}
{
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();

        }
}
void Location::positionUpdated(const QGeoPositionInfo &info)
{
        qDebug() << "Position updated:" << info;
        std::cout << "Ispis:" << std::endl;
        std::cout << &info << std::endl;

        QGeoCoordinate coordinate = info.coordinate();
        qreal latitude = coordinate.latitude();
        qreal longitude = coordinate.longitude();
        qreal altitude = coordinate.altitude();

        qDebug() << "Latitude:" << latitude << "Longitude:" << longitude << "Altitude:" << altitude;
}
