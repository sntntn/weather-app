#include "Settings.h"

#include <QVariantMap>
#include <QVariantList>

#include "GeoLocationData.h"
#include "Serializer.h"

const QMap<Settings::TemperatureUnit, QString> Settings::temperatureUnitToApiParameter
{
    {Settings::TemperatureUnit::CELSIUS, "celsius"},
    {Settings::TemperatureUnit::FAHRENHEIT, "fahrenheit"}
};

const QMap<Settings::WindSpeedUnit, QString> Settings::windSpeedUnitToApiParameter
{
    {Settings::WindSpeedUnit::KMH, "kmh"},
    {Settings::WindSpeedUnit::MPH, "mph"},
    {Settings::WindSpeedUnit::MS, "ms"},
    {Settings::WindSpeedUnit::KNOTS, "kn"}
};

const QMap<Settings::PrecipitationUnit, QString> Settings::precipitationUnitToApiParameter
{
    {Settings::PrecipitationUnit::MILLIMETRES, "mm"},
    {Settings::PrecipitationUnit::INCHES, "inch"}
};

const QMap<Settings::TemperatureUnit, QString> Settings::temperatureUnitToString
{
    {Settings::TemperatureUnit::CELSIUS, "°C"},
    {Settings::TemperatureUnit::FAHRENHEIT, "°F"}
};

const QMap<Settings::WindSpeedUnit, QString> Settings::windSpeedUnitToString
{
    {Settings::WindSpeedUnit::KMH, "km/h"},
    {Settings::WindSpeedUnit::MPH, "mph"},
    {Settings::WindSpeedUnit::MS, "m/s"},
    {Settings::WindSpeedUnit::KNOTS, "kn"}
};

const QMap<Settings::PrecipitationUnit, QString> Settings::precipitationUnitToString
{
    {Settings::PrecipitationUnit::MILLIMETRES, "mm"},
    {Settings::PrecipitationUnit::INCHES, "in"}
};

const QMap<Settings::TemperatureUnit, QString> Settings::temperatureUnitsNames{
    {Settings::TemperatureUnit::CELSIUS, "Celsius"},
    {Settings::TemperatureUnit::FAHRENHEIT, "Fahrenheit"}
};

const QMap<Settings::WindSpeedUnit, QString> Settings::windSpeedUnitsNames
{
        {Settings::WindSpeedUnit::KMH, "Kilometres per hour"},
        {Settings::WindSpeedUnit::MPH, "Miles per hour"},
        {Settings::WindSpeedUnit::MS, "Metres per second"},
        {Settings::WindSpeedUnit::KNOTS, "Knots"}
};

const QMap<Settings::PrecipitationUnit, QString> Settings::precipitationUnitsNames
{
        {Settings::PrecipitationUnit::MILLIMETRES, "Millimetres"},
        {Settings::PrecipitationUnit::INCHES, "Inches"}
};


Settings::Settings()
{
    Serializer serializer;
    serializer.load(*this, "../Serialization/settings.json");
}

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

QVariant Settings::toVariant() const
{
    QVariantMap map;
    map.insert("shareLocation", shareLocation);
    map.insert("temperatureUnit", temperatureUnit);
    map.insert("windSpeedUnit", windSpeedUnit);
    map.insert("precipitationUnit", precipitationUnit);
    QVariantList locations;
    for (const auto &savedLocation : savedLocations){
        QVariantMap location = savedLocation.toVariant().toMap();
        locations.append(location);
    }
    map.insert("locations", locations);

    return map;
}

void Settings::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    shareLocation = map.value("shareLocation").toBool();
    temperatureUnit = map.value("temperatureUnit").value<Settings::TemperatureUnit>();
    windSpeedUnit = map.value("precipitationUnit").value<Settings::WindSpeedUnit>();
    precipitationUnit = map.value("precipitationUnit").value<Settings::PrecipitationUnit>();

    const auto locations = map.value("locations").toList();
    for(const auto& location : locations){
        const auto geoLocation = location.toMap();
        savedLocations.append(GeoLocationData::fromVariantMap(geoLocation));
    }
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
