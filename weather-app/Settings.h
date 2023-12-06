#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QMap>

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

    QString temperatureUnitApiParameter();
    QString windSpeedUnitApiParameter();
    QString precipitationUnitApiParameter();

    QString temperatureUnitString();
    QString windSpeedUnitString();
    QString precipitationUnitString();

    QString temperatureUnitName();
    QString windSpeedUnitName();
    QString precipitationUnitName();

    bool shareLocation;
    TemperatureUnit temperatureUnit;
    WindSpeedUnit windSpeedUnit;
    PrecipitationUnit precipitationUnit;

    static QMap<TemperatureUnit, QString> temperatureUnitToString;
    static QMap<WindSpeedUnit, QString> windSpeedUnitToString;
    static QMap<PrecipitationUnit, QString> precipitationUnitToString;

    static QMap<TemperatureUnit, QString> temperatureUnitToApiParameter;
    static QMap<WindSpeedUnit, QString> windSpeedUnitToApiParameter;
    static QMap<PrecipitationUnit, QString> precipitationUnitToApiParameter;

    static QMap<TemperatureUnit, QString> temperatureUnitsNames;
    static QMap<WindSpeedUnit, QString> windSpeedUnitsNames;
    static QMap<PrecipitationUnit, QString> precipitationUnitsNames;

private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
};

#endif // SETTINGS_H
