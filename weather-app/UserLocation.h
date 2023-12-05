#ifndef USERLOCATION_H
#define USERLOCATION_H

#include <QGeoPositionInfoSource>

class GeoLocationData;

class UserLocation : public QObject
{
    Q_OBJECT
public:
    explicit UserLocation(QObject *parent = nullptr);

private:
    QGeoPositionInfoSource *source;

private slots:
    void positionUpdated(const QGeoPositionInfo &info);

signals:
    void userLocationFetched(const QSharedPointer<GeoLocationData> &data);
};

#endif // USERLOCATION_H
