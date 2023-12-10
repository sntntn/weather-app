#include "Settings.h"

#include "GeoLocationData.h"

const QMap<TemperatureUnit, QString> Settings::temperatureUnitToApiParameter{
    {TemperatureUnit::CELSIUS, "celsius"},
    {TemperatureUnit::FAHRENHEIT, "fahrenheit"}
};

const QMap<WindSpeedUnit, QString> Settings::windSpeedUnitToApiParameter
{
    {WindSpeedUnit::KMH, "kmh"},
    {WindSpeedUnit::MPH, "mph"},
    {WindSpeedUnit::MS, "ms"},
    {WindSpeedUnit::KNOTS, "kn"}
};

const QMap<PrecipitationUnit, QString> Settings::precipitationUnitToApiParameter
{
    {PrecipitationUnit::MILLIMETRES, "mm"},
    {PrecipitationUnit::INCHES, "inch"}
};

const QMap<TemperatureUnit, QString> Settings::temperatureUnitToString
{
    {TemperatureUnit::CELSIUS, "°C"},
    {TemperatureUnit::FAHRENHEIT, "°F"}
};

const QMap<WindSpeedUnit, QString> Settings::windSpeedUnitToString
{
    {WindSpeedUnit::KMH, "km/h"},
    {WindSpeedUnit::MPH, "mph"},
    {WindSpeedUnit::MS, "m/s"},
    {WindSpeedUnit::KNOTS, "kn"}
};

const QMap<PrecipitationUnit, QString> Settings::precipitationUnitToString
{
    {PrecipitationUnit::MILLIMETRES, "mm"},
    {PrecipitationUnit::INCHES, "in"}
};

const QMap<TemperatureUnit, QString> Settings::temperatureUnitsNames{
    {TemperatureUnit::CELSIUS, "Celsius"},
    {TemperatureUnit::FAHRENHEIT, "Fahrenheit"}
};

const QMap<WindSpeedUnit, QString> Settings::windSpeedUnitsNames
    {
        {WindSpeedUnit::KMH, "Kilometres per hour"},
        {WindSpeedUnit::MPH, "Miles per hour"},
        {WindSpeedUnit::MS, "Metres per second"},
        {WindSpeedUnit::KNOTS, "Knots"}
    };

const QMap<PrecipitationUnit, QString> Settings::precipitationUnitsNames
    {
        {PrecipitationUnit::MILLIMETRES, "Millimetres"},
        {PrecipitationUnit::INCHES, "Inches"}
    };


//TODO serijalizacija
Settings::Settings()
    : shareLocation(false)
    , temperatureUnit(TemperatureUnit::CELSIUS)
    , windSpeedUnit(WindSpeedUnit::KMH)
    , precipitationUnit(PrecipitationUnit::MILLIMETRES)
{
    //TODO serijalizacija
        auto location1 = GeoLocationData("Belgrade, City of Belgrade, Serbia", "Belgrade", QGeoCoordinate(44.8178, 20.4569));
        auto location2 = GeoLocationData("Berlin, Germany", "Berlin", QGeoCoordinate(52.517, 12.3889));
        auto location3 = GeoLocationData("Paris, Ile-de-France, France", "Paris", QGeoCoordinate(48.8589, 2.32004));
        auto location4 = GeoLocationData("Athens, Central Athens, Greece", "Athens", QGeoCoordinate(37.9756,23.7348));
        savedLocations.push_back(location1);
        savedLocations.push_back(location2);
        savedLocations.push_back(location3);
        savedLocations.push_back(location4);
}

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

QString Settings::temperatureUnitApiParameter() const
{
    return temperatureUnitToApiParameter[temperatureUnit];
}

QString Settings::windSpeedUnitApiParameter() const
{
    return windSpeedUnitToApiParameter[windSpeedUnit];
}

QString Settings::precipitationUnitApiParameter() const
{
    return precipitationUnitToApiParameter[precipitationUnit];
}

QString Settings::temperatureUnitString() const
{
    return temperatureUnitToString[temperatureUnit];
}

QString Settings::windSpeedUnitString() const
{
    return windSpeedUnitToString[windSpeedUnit];
}

QString Settings::precipitationUnitString() const
{
    return precipitationUnitToString[precipitationUnit];
}

QString Settings::temperatureUnitName() const
{
    return temperatureUnitsNames[temperatureUnit];
}

QString Settings::windSpeedUnitName() const
{
    return windSpeedUnitsNames[windSpeedUnit];
}

QString Settings::precipitationUnitName() const
{
    return precipitationUnitsNames[precipitationUnit];
}
