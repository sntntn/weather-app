#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QMap>

class GeoLocationData;

enum class TemperatureUnit
{
    CELSIUS,
    FAHRENHEIT
};

enum class WindSpeedUnit
{
    KMH,
    MPH,
    MS,
    KNOTS
};

enum class PrecipitationUnit
{
    MILLIMETRES,
    INCHES
};


class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings& instance();
    // TODO setters and getters or public variables
    // void setLocationSharing(const bool);
    // void setTemperatureUnit(const TemperatureUnit);
    // void setWindSpeedUnit(const WindSpeedUnit);
    // void setPrecipitationUnit(const PrecipitationUnit);

    QString temperatureUnitApiParameter() const;
    QString windSpeedUnitApiParameter() const;
    QString precipitationUnitApiParameter() const;

    QString temperatureUnitString() const;
    QString windSpeedUnitString() const;
    QString precipitationUnitString() const;

    QString temperatureUnitName() const;
    QString windSpeedUnitName() const;
    QString precipitationUnitName() const;

    bool shareLocation;
    TemperatureUnit temperatureUnit;
    WindSpeedUnit windSpeedUnit;
    PrecipitationUnit precipitationUnit;
    QList<GeoLocationData> savedLocations;

    static const QMap<TemperatureUnit, QString> temperatureUnitToString;
    static const QMap<WindSpeedUnit, QString> windSpeedUnitToString;
    static const QMap<PrecipitationUnit, QString> precipitationUnitToString;

    static const QMap<TemperatureUnit, QString> temperatureUnitToApiParameter;
    static const QMap<WindSpeedUnit, QString> windSpeedUnitToApiParameter;
    static const QMap<PrecipitationUnit, QString> precipitationUnitToApiParameter;

    static const QMap<TemperatureUnit, QString> temperatureUnitsNames;
    static const QMap<WindSpeedUnit, QString> windSpeedUnitsNames;
    static const QMap<PrecipitationUnit, QString> precipitationUnitsNames;

private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
};

#endif // SETTINGS_H
