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

    inline QList<GeoLocationData> &savedLocations()
    {
        return m_savedLocations;
    }

    inline bool shareLocation() const
    {
        return m_shareLocation;
    }

private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QString temperatureUnitToApiParameter(TemperatureUnit tempUnit) const;
    QString windSpeedUnitToApiParameter(WindSpeedUnit windSpeedUnit) const;
    QString precipitationUnitToApiParameter(PrecipitationUnit precUnit) const;

    QString temperatureUnitToString(TemperatureUnit tempUnit) const;
    QString windSpeedUnitToString(WindSpeedUnit windSpeedUnit) const;
    QString precipitationUnitToString(PrecipitationUnit precUnit) const;

    QString temperatureUnitsNames(TemperatureUnit tempUnit) const;
    QString windSpeedUnitsNames(WindSpeedUnit precUnit) const;
    QString precipitationUnitsNames(PrecipitationUnit precUnit) const;

    Settings::TemperatureUnit m_temperatureUnit = TemperatureUnit::CELSIUS;
    Settings::WindSpeedUnit m_windSpeedUnit = WindSpeedUnit::KMH;
    Settings::PrecipitationUnit m_precipitationUnit = PrecipitationUnit::MILLIMETRES;

    bool m_shareLocation = false;
    QList<GeoLocationData> m_savedLocations;

    friend class SettingsDialog;
};

#endif // SETTINGS_H
