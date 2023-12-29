#include "catch.hpp"

#include <QString>

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
}

