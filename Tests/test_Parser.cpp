#include "catch.hpp"

#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "GeoLocationData.h"
#include "Parser.h"

TEST_CASE("WeatherData parser")
{

  SECTION("Test parseWeatherData with real JSON from open-meteo")
  {
	// Arrange
	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");

	std::ifstream	  file("../Tests/Resources/weatherData.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string jsonData = buffer.str();

	// Act
	auto data = Parser::parseWeatherData(QString::fromStdString(jsonData), location);

	// Assert
	REQUIRE_FALSE(nullptr == data);
  }

  SECTION("Test parseWeatherData with invalid JSON")
  {
	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	QString			invalidJson = "This is not a valid JSON string";
	REQUIRE(nullptr == Parser::parseWeatherData(invalidJson, location));
  }

  SECTION("Test parseWeatherData with missing fields")
  {
	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	QString			jsonWithoutFields = "{\"timezone\": \"Europe/Belgrade\"}";
	REQUIRE(nullptr == Parser::parseWeatherData(jsonWithoutFields, location));
  }

  SECTION("Test parseWeatherData with valid JSON")
  {
	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	QString			validJson = R"({
            "timezone": "Europe/Belgrade",
            "current": { "temperature_2m": 25, "weather_code": 800, "is_day": 1 },
            "daily": { "temperature_2m_max": [28], "temperature_2m_min": [20] }
        })";
	REQUIRE_FALSE(nullptr == Parser::parseWeatherData(validJson, location));
  }
}

TEST_CASE("parseGeocodingData")
{

  SECTION("Test with valid JSON data")
  {

	QJsonArray	resultsArray;
	QJsonObject resultObject1, resultObject2;

	resultObject1["formatted"] = "Belgrade, Serbia";
	QJsonObject geometryObject1;
	geometryObject1["lat"]	  = 44.7866;
	geometryObject1["lng"]	  = 20.4489;
	resultObject1["geometry"] = geometryObject1;
	QJsonObject componentsObject1;
	componentsObject1["country"] = "Serbia";
	resultObject1["components"]	 = componentsObject1;
	resultsArray.append(resultObject1);

	resultObject2["formatted"] = "Paris, France";
	QJsonObject geometryObject2;
	geometryObject2["lat"]	  = 48.8566;
	geometryObject2["lng"]	  = 2.3522;
	resultObject2["geometry"] = geometryObject2;
	QJsonObject componentsObject2;
	componentsObject2["country"] = "France";
	resultObject2["components"]	 = componentsObject2;
	resultsArray.append(resultObject2);

	QList<GeoLocationData> locations;
	Parser::parseGeocodingData(resultsArray, locations);

	REQUIRE(locations.size() == 2);
  }

  SECTION("Test with valid JSON data, but missing country")
  {
	QJsonArray	resultsArray;
	QJsonObject resultObject;

	resultObject["formatted"] = "Belgrade, Serbia";
	QJsonObject geometryObject;
	geometryObject["lat"]	 = 44.7866;
	geometryObject["lng"]	 = 20.4489;
	resultObject["geometry"] = geometryObject;
	resultsArray.append(resultObject);

	QList<GeoLocationData> locations;
	Parser::parseGeocodingData(resultsArray, locations);

	REQUIRE(locations.size() == 1);
  }

  SECTION("Test with valid JSON data, but missing entire componentsObject")
  {
	QJsonArray	resultsArray;
	QJsonObject resultObject;

	resultObject["formatted"] = "Belgrade, Serbia";
	QJsonObject geometryObject;
	geometryObject["lat"]	 = 44.7866;
	geometryObject["lng"]	 = 20.4489;
	resultObject["geometry"] = geometryObject;
	QJsonObject componentsObject;
	resultObject["components"] = componentsObject;
	resultsArray.append(resultObject);

	QList<GeoLocationData> locations;
	Parser::parseGeocodingData(resultsArray, locations);

	REQUIRE(locations.size() == 1);
  }

  SECTION("Test with invalid JSON data, missing required fields")
  {
	QJsonArray	resultsArray;
	QJsonObject invalidResultObject;
	invalidResultObject["formatted"] = "Invalid Place";
	resultsArray.append(invalidResultObject);

	QList<GeoLocationData> locations;
	Parser::parseGeocodingData(resultsArray, locations);

	REQUIRE(locations.isEmpty());
  }

  SECTION("Test with invalid JSON data, missing lat and lng")
  {
	QJsonArray	resultsArray;
	QJsonObject resultObject;

	resultObject["formatted"] = "Belgrade, Serbia";
	QJsonObject geometryObject;
	resultObject["geometry"] = geometryObject;
	QJsonObject componentsObject;
	componentsObject["country"] = "Serbia";
	resultObject["components"]	= componentsObject;
	resultsArray.append(resultObject);

	QList<GeoLocationData> locations;
	Parser::parseGeocodingData(resultsArray, locations);

	REQUIRE(locations.isEmpty());
  }

  SECTION("Test with invalid JSON data, missing formatted")
  {
	QJsonArray	resultsArray;
	QJsonObject resultObject;

	QJsonObject geometryObject;
	geometryObject["lat"]	 = 44.7866;
	geometryObject["lng"]	 = 20.4489;
	resultObject["geometry"] = geometryObject;
	QJsonObject componentsObject;
	componentsObject["country"] = "Serbia";
	resultObject["components"]	= componentsObject;
	resultsArray.append(resultObject);

	QList<GeoLocationData> locations;
	Parser::parseGeocodingData(resultsArray, locations);

	REQUIRE(locations.isEmpty());
  }
}
