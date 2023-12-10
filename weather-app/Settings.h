#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QMap>

#include "Serializable.h"

class GeoLocationData;

class Settings : public QObject, public Serializable
{
    Q_OBJECT

public:
    static Settings& instance();

    enum TemperatureUnit
    {
        CELSIUS,
        FAHRENHEIT
    };
    Q_ENUM(TemperatureUnit)

    enum WindSpeedUnit
    {
        KMH,
        MPH,
        MS,
        KNOTS
    };
    Q_ENUM(WindSpeedUnit)

    enum PrecipitationUnit
    {
        MILLIMETRES,
        INCHES
    };
    Q_ENUM(PrecipitationUnit)


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

    QVariant toVariant() const override;
    void fromVariant(const QVariant & variant) override;

    bool shareLocation = false;
    Settings::TemperatureUnit temperatureUnit = TemperatureUnit::CELSIUS;
    Settings::WindSpeedUnit windSpeedUnit = WindSpeedUnit::KMH;
    Settings::PrecipitationUnit precipitationUnit = PrecipitationUnit::MILLIMETRES;
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
