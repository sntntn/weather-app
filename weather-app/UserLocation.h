#ifndef USERLOCATION_H
#define USERLOCATION_H

#include <QGeoPositionInfoSource>

class GeoLocationData;

class UserLocation : public QObject
{
    Q_OBJECT
public:
    explicit UserLocation(QObject *parent = nullptr);
    void getLocation();

private:
    QGeoPositionInfoSource *source;

private slots:
    void positionUpdated(const QGeoPositionInfo &info);

signals:
    void userLocationFetched(const GeoLocationData &data);
};

#endif // USERLOCATION_H
