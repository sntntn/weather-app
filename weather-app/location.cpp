#include "location.h"

Location::Location(QObject* parent)
    : QObject{parent}
{
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();

        std::cout << "Ispis:" << std::endl;
        std::cout << source << std::endl;

        }
}
void Location::positionUpdated(const QGeoPositionInfo &info)
{
        qDebug() << "Position updated:" << info;
}
