#include "catch.hpp"

#include <QString>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Parser.h"
#include "GeoLocationData.h"

TEST_CASE("WeatherData parser"){

    SECTION("Test parseWeatherData with real JSON from open-meteo"){
        // Arrange
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");

        std::ifstream file("../Tests/Resources/weatherData.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonData = buffer.str();

        // Act

        // Assert
        REQUIRE_FALSE( nullptr == Parser::parseWeatherData(QString::fromStdString(jsonData), location) );
    }

    SECTION("Test parseWeatherData with invalid JSON") {
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QString invalidJson = "This is not a valid JSON string";
        REQUIRE(nullptr == Parser::parseWeatherData(invalidJson, location));
    }

    SECTION("Test parseWeatherData with missing fields") {
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QString jsonWithoutFields = "{\"timezone\": \"Europe/Belgrade\"}";
        REQUIRE(nullptr == Parser::parseWeatherData(jsonWithoutFields, location));
    }

    SECTION("Test parseWeatherData with valid JSON") {
        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QString validJson = R"({
            "timezone": "Europe/Belgrade",
            "current": { "temperature_2m": 25, "weather_code": 800, "is_day": 1 },
            "daily": { "temperature_2m_max": [28], "temperature_2m_min": [20] }
        })";
        REQUIRE_FALSE(nullptr == Parser::parseWeatherData(validJson, location));
    }
}


#include "catch.hpp"
#include "Parser.h"

TEST_CASE("parseGeocodingData") {

    SECTION("Test with invalid JSON data, missing required fields") {
        QJsonArray resultsArray;
        QJsonObject invalidResultObject;
        invalidResultObject["formatted"] = "Invalid Place";
        resultsArray.append(invalidResultObject);

        QList<GeoLocationData> locations;
        Parser::parseGeocodingData(resultsArray, locations);

        //onda je prazna
        REQUIRE(locations.isEmpty());
    }
}



