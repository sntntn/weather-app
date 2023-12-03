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
    void setLocationSharing(const bool);
    void setTemperatureUnit(const TemperatureUnit);
    void setWindSpeedUnit(const WindSpeedUnit);
    void setPrecipitationUnit(const PrecipitationUnit);

    QString temperatureUnitApiParameter();
    QString windSpeedUnitApiParameter();
    QString precipitationUnitApiParameter();

    QString temperatureUnitString();
    QString windSpeedUnitString();
    QString precipitationUnitString();

    bool shareLocation;
    TemperatureUnit temperatureUnit;
    WindSpeedUnit windSpeedUnit;
    PrecipitationUnit precipitationUnit;

private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    static QMap<TemperatureUnit, QString> temperatureUnitToApiParameter;
    static QMap<WindSpeedUnit, QString> windSpeedUnitToApiParameter;
    static QMap<PrecipitationUnit, QString> precipitationUnitToApiParameter;

    static QMap<TemperatureUnit, QString> temperatureUnitToString;
    static QMap<WindSpeedUnit, QString> windSpeedUnitToString;
    static QMap<PrecipitationUnit, QString> precipitationUnitToString;
};

#endif // SETTINGS_H
