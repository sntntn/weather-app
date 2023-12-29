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
        REQUIRE_FALSE( nullptr == Parser::parseWeatherData(QString::fromStdString(jsonData), *location) );
    }
}

