#include "catch.hpp"

#include <QString>
#include <QVariant>

#include "GeoLocationData.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include "HomePage.h"

TEST_CASE("Test Settings class reachable functions"){

    SECTION("Test if function weatherCodeToIcon returns correct path to icon"){
        // Arrange
        int weatherCode = 65;
        bool isDay = false;

        // Act
        QString iconPath = Settings::instance().weatherCodeToIcon(weatherCode, isDay);

        // Assert
        REQUIRE(iconPath == "../Resources/weatherIcons/HeavyRainSwrsNight.png");
    }

    SECTION("Test if function toVariant correctly saves shareLocation value"){
        // Arrange
        bool shareLocation = Settings::instance().shareLocation();

        // Act
        auto map = Settings::instance().toVariant().toMap();

        // Assert
        REQUIRE(map.value("shareLocation").toBool() == shareLocation);
    }

    SECTION("Test if function toVariant correctly saves locations"){
        // Arrange
        QList<GeoLocationData> savedLocations = Settings::instance().savedLocations();

        // Act
        auto map = Settings::instance().toVariant().toMap();

        QList<GeoLocationData> savedLocationsFromVariant;

        const auto locations = map.value("locations").toList();
        for(const auto& location : locations){
            const auto geoLocation = location.toMap();
            savedLocationsFromVariant.append(GeoLocationData::fromVariantMap(geoLocation));
        }
        // Assert
        REQUIRE(savedLocations == savedLocationsFromVariant);
    }

    SECTION("Test if function fromVariant correctly sets Settings variable"){
        // Arrange
        QVariantMap map;
        bool shareLocation = true;
        map.insert("shareLocation", shareLocation);
        map.insert("temperatureUnit", QVariant::fromValue(Settings::TemperatureUnit::CELSIUS));
        map.insert("windSpeedUnit", QVariant::fromValue(Settings::WindSpeedUnit::KMH));
        map.insert("precipitationUnit", QVariant::fromValue(Settings::PrecipitationUnit::MILLIMETRES));

        QList<QVariant> locationList;
        QList<GeoLocationData> geoLocationList;
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        geoLocationList.append(location);
        locationList.append(QVariant::fromValue(location));
        map.insert("locations", QVariant::fromValue(locationList));

        // Act
        Settings::instance().fromVariant(map);

        // Assert
        REQUIRE(shareLocation == Settings::instance().shareLocation());
    }

    SECTION("Settings serialization and deserialization") {
        // Arrange - setup original settings
        bool shareLocation = Settings::instance().shareLocation();

        // Act - Deserialize settings from QVariant
        QVariant map = Settings::instance().toVariant();
        Settings::instance().fromVariant(map);

        // Assert - Check if settings were restored correctly
        REQUIRE(shareLocation == Settings::instance().shareLocation());
    }

}

