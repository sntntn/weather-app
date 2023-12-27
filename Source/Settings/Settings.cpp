#include "Settings.h"

#include <QVariantMap>
#include <QVariantList>

#include "GeoLocationData.h"
#include "Serializer.h"

QString Settings::temperatureUnitToApiParameter(const TemperatureUnit tempUnit) const{
    switch (tempUnit) {
    case Settings::TemperatureUnit::CELSIUS:
        return "celsius";
    case Settings::TemperatureUnit::FAHRENHEIT:
        return "fahrenheit";
    default:
        return "";
    }
}
QString Settings::windSpeedUnitToApiParameter(const WindSpeedUnit windSpeedUnit) const{
    switch (windSpeedUnit) {
    case Settings::WindSpeedUnit::KMH:
        return "kmh";
    case Settings::WindSpeedUnit::MPH:
        return "mph";
    case Settings::WindSpeedUnit::MS:
        return "ms";
    case Settings::WindSpeedUnit::KNOTS:
        return "kn";
    default:
        return "";
    }
}
QString Settings::precipitationUnitToApiParameter(const PrecipitationUnit precUnit) const{
    switch (precUnit) {
    case Settings::PrecipitationUnit::MILLIMETRES:
        return "mm";
    case Settings::PrecipitationUnit::INCHES:
        return "inch";
    default:
        return "";
    }
}

QString Settings::temperatureUnitToString(const TemperatureUnit tempUnit) const{
    switch (tempUnit) {
    case Settings::TemperatureUnit::CELSIUS:
        return "°C";
    case Settings::TemperatureUnit::FAHRENHEIT:
        return "°F";
    default:
        return "";
    }
}

QString Settings::windSpeedUnitToString(const WindSpeedUnit windSpeedUnit) const{
    switch (windSpeedUnit) {
    case Settings::WindSpeedUnit::KMH:
        return "km/h";
    case Settings::WindSpeedUnit::MPH:
        return "mph";
    case Settings::WindSpeedUnit::MS:
        return "m/s";
    case Settings::WindSpeedUnit::KNOTS:
        return "kn";
    default:
        return "";
    }
}
QString Settings::precipitationUnitToString(const PrecipitationUnit precUnit) const{
    switch (precUnit) {
    case Settings::PrecipitationUnit::MILLIMETRES:
        return "mm";
    case Settings::PrecipitationUnit::INCHES:
        return "in";
    default:
        return "";
    }
}

QString Settings::temperatureUnitsNames(const TemperatureUnit tempUnit) const{
    switch (tempUnit) {
    case Settings::TemperatureUnit::CELSIUS:
        return "Celsius";
    case Settings::TemperatureUnit::FAHRENHEIT:
        return "Fahrenheit";
    default:
        return "";
    }
}
QString Settings::windSpeedUnitsNames(const WindSpeedUnit windSpeedUnit) const{
    switch (windSpeedUnit) {
    case Settings::WindSpeedUnit::KMH:
        return "Kilometres per hour";
    case Settings::WindSpeedUnit::MPH:
        return "Miles per hour";
    case Settings::WindSpeedUnit::MS:
        return "Metres per second";
    case Settings::WindSpeedUnit::KNOTS:
        return "Knots";
    default:
        return "";
    }
}
QString Settings::precipitationUnitsNames(const PrecipitationUnit precUnit) const{
    switch (precUnit) {
    case Settings::PrecipitationUnit::MILLIMETRES:
        return "Millimetres";
    case Settings::PrecipitationUnit::INCHES:
        return "Inches";
    default:
        return "";
    }
}

Settings::Settings()
{
    Serializer::load(*this, "../Serialization/settings.json");
}

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

QVariant Settings::toVariant() const
{
    QVariantMap map;
    map.insert("shareLocation", m_shareLocation);
    map.insert("temperatureUnit", m_temperatureUnit);
    map.insert("windSpeedUnit", m_windSpeedUnit);
    map.insert("precipitationUnit", m_precipitationUnit);
    QVariantList locations;
    for (const auto &savedLocation : m_savedLocations){
        QVariantMap location = savedLocation.toVariant().toMap();
        locations.append(location);
    }
    map.insert("locations", locations);

    return map;
}

void Settings::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    m_shareLocation = map.value("shareLocation").toBool();
    m_temperatureUnit = map.value("temperatureUnit").value<Settings::TemperatureUnit>();
    m_windSpeedUnit = map.value("precipitationUnit").value<Settings::WindSpeedUnit>();
    m_precipitationUnit = map.value("precipitationUnit").value<Settings::PrecipitationUnit>();

    const auto locations = map.value("locations").toList();
    for(const auto& location : locations){
        const auto geoLocation = location.toMap();
        m_savedLocations.append(GeoLocationData::fromVariantMap(geoLocation));
    }
}

QString Settings::temperatureUnitApiParameter() const
{
    return temperatureUnitToApiParameter(m_temperatureUnit);
}

QString Settings::windSpeedUnitApiParameter() const
{
    return windSpeedUnitToApiParameter(m_windSpeedUnit);
}

QString Settings::precipitationUnitApiParameter() const
{
    return precipitationUnitToApiParameter(m_precipitationUnit);
}

QString Settings::temperatureUnitString() const
{
    return temperatureUnitToString(m_temperatureUnit);
}

QString Settings::windSpeedUnitString() const
{
    return windSpeedUnitToString(m_windSpeedUnit);
}

QString Settings::precipitationUnitString() const
{
    return precipitationUnitToString(m_precipitationUnit);
}

QString Settings::temperatureUnitName() const
{
    return temperatureUnitsNames(m_temperatureUnit);
}

QString Settings::windSpeedUnitName() const
{
    return windSpeedUnitsNames(m_windSpeedUnit);
}

QString Settings::precipitationUnitName() const
{
    return precipitationUnitsNames(m_precipitationUnit);
}
