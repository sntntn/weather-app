#include "Settings.h"

QMap<TemperatureUnit, QString> Settings::temperatureUnitToApiParameter{
    {TemperatureUnit::CELSIUS, "celsius"},
    {TemperatureUnit::FAHRENHEIT, "fahrenheit"}
};

QMap<WindSpeedUnit, QString> Settings::windSpeedUnitToApiParameter
{
    {WindSpeedUnit::KMH, "kmh"},
    {WindSpeedUnit::MPH, "mph"},
    {WindSpeedUnit::MS, "ms"},
    {WindSpeedUnit::KNOTS, "kn"}
};

QMap<PrecipitationUnit, QString> Settings::precipitationUnitToApiParameter
{
    {PrecipitationUnit::MILLIMETRES, "mm"},
    {PrecipitationUnit::INCHES, "inch"}
};

QMap<TemperatureUnit, QString> Settings::temperatureUnitToString
{
    {TemperatureUnit::CELSIUS, "°C"},
    {TemperatureUnit::FAHRENHEIT, "°F"}
};

QMap<WindSpeedUnit, QString> Settings::windSpeedUnitToString
{
    {WindSpeedUnit::KMH, "km/h"},
    {WindSpeedUnit::MPH, "mph"},
    {WindSpeedUnit::MS, "m/s"},
    {WindSpeedUnit::KNOTS, "kn"}
};

QMap<PrecipitationUnit, QString> Settings::precipitationUnitToString
{
    {PrecipitationUnit::MILLIMETRES, "mm"},
    {PrecipitationUnit::INCHES, "in"}
};

Settings::Settings()
    : shareLocation(false)
    , temperatureUnit(TemperatureUnit::CELSIUS)
    , windSpeedUnit(WindSpeedUnit::KMH)
    , precipitationUnit(PrecipitationUnit::MILLIMETRES)
{ }

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

QString Settings::temperatureUnitApiParameter()
{
    return temperatureUnitToApiParameter[temperatureUnit];
}

QString Settings::windSpeedUnitApiParameter()
{
    return windSpeedUnitToApiParameter[windSpeedUnit];
}

QString Settings::precipitationUnitApiParameter()
{
    return precipitationUnitToApiParameter[precipitationUnit];
}

QString Settings::temperatureUnitString()
{
    return temperatureUnitToString[temperatureUnit];
}

QString Settings::windSpeedUnitString()
{
    return windSpeedUnitToString[windSpeedUnit];
}

QString Settings::precipitationUnitString()
{
    return precipitationUnitToString[precipitationUnit];
}
