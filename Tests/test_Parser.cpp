#include "catch.hpp"

#include <QString>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Parser.h"
#include "GeoLocationData.h"

TEST_CASE("Test Parser class"){

    SECTION("Test function parseWeatherData"){
        // Arrange
        GeoLocationData *location = new GeoLocationData("Belgrade", "Belgrade",
                                                       QGeoCoordinate(44.8125, 20.4375), "Serbia");

        std::ifstream file("../Tests/Resources/weatherData.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonData = buffer.str();
        // Act

        // Assert
        REQUIRE_NOTHROW( Parser::parseWeatherData(QString::fromStdString(jsonData), *location) );
    }
}

TEST_CASE("Parser Tests") {

    SECTION("Test parseWeatherData with invalid JSON") {
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QString invalidJson = "This is not a valid JSON string";
        REQUIRE_THROWS_AS(Parser::parseWeatherData(invalidJson, location), std::runtime_error);
    }

    SECTION("Test parseWeatherData with missing fields") {
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QString jsonWithoutFields = "{\"timezone\": \"Europe/Belgrade\"}";
        REQUIRE_THROWS_AS(Parser::parseWeatherData(jsonWithoutFields, location), std::runtime_error);
    }

    SECTION("Test parseWeatherData with valid JSON") {
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QString validJson = R"({
            "timezone": "Europe/Belgrade",
            "current": { "temperature_2m": 25, "weather_code": 800, "is_day": 1 },
            "daily": { "temperature_2m_max": [28], "temperature_2m_min": [20] }
        })";
        REQUIRE_NOTHROW(Parser::parseWeatherData(validJson, location));
    }


}
