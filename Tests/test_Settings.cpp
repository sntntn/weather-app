#include "catch.hpp"

#include <QString>
#include <QVariant>

#include "GeoLocationData.h"
#include "HomePage.h"
#include "Settings.h"
#include "SettingsDialog.h"

TEST_CASE("Test Settings class reachable functions")
{

  SECTION("Test if function weatherCodeToIcon returns correct path to icon")
  {
	// Arrange
	int	 weatherCode = 65;
	bool isDay		 = false;

	// Act
	QString iconPath = Settings::instance().weatherCodeToIcon(weatherCode, isDay);

	// Assert
	REQUIRE(iconPath == "../Resources/weatherIcons/HeavyRainSwrsNight.png");
  }

  SECTION("Test if temperatureUnitApiParameter function correctly converts "
		  "temperature unit to api parameter")
  {
	// Arrange
	Settings::TemperatureUnit temperatureUnit = Settings::instance().tempUnit();

	// Act
	QString tempApiParam = Settings::instance().temperatureUnitApiParameter();

	// Assert
	switch (temperatureUnit)
	{
	case Settings::TemperatureUnit::CELSIUS:
	  REQUIRE(tempApiParam == "celsius");
	  break;
	case Settings::TemperatureUnit::FAHRENHEIT:
	  REQUIRE(tempApiParam == "fahrenheit");
	  break;
	default:
	  REQUIRE(tempApiParam == "");
	  break;
	}
  }

  SECTION("Test if temperatureUnitString function correctly converts "
		  "temperature unit to string")
  {
	// Arrange
	Settings::TemperatureUnit temperatureUnit = Settings::instance().tempUnit();

	// Act
	QString tempString = Settings::instance().temperatureUnitString();

	// Assert
	switch (temperatureUnit)
	{
	case Settings::TemperatureUnit::CELSIUS:
	  REQUIRE(tempString == "°C");
	  break;
	case Settings::TemperatureUnit::FAHRENHEIT:
	  REQUIRE(tempString == "°F");
	  break;
	default:
	  REQUIRE(tempString == "");
	  break;
	}
  }

  SECTION("Test if temperatureUnitsNames function correctly converts "
		  "temperature unit to name")
  {
	// Arrange
	Settings::TemperatureUnit temperatureUnit = Settings::instance().tempUnit();

	// Act
	QString tempName = Settings::instance().temperatureUnitName();

	// Assert
	switch (temperatureUnit)
	{
	case Settings::TemperatureUnit::CELSIUS:
	  REQUIRE(tempName == "Celsius");
	  break;
	case Settings::TemperatureUnit::FAHRENHEIT:
	  REQUIRE(tempName == "Fahrenheit");
	  break;
	default:
	  REQUIRE(tempName == "");
	  break;
	}
  }

  SECTION("Test if function toVariant correctly saves shareLocation and temperature unit value")
  {
	// Arrange
	bool					  shareLocation	  = Settings::instance().shareLocation();
	Settings::TemperatureUnit temperatureUnit = Settings::instance().tempUnit();

	// Act
	auto map = Settings::instance().toVariant().toMap();

	// Assert
	REQUIRE(map.value("shareLocation").toBool() == shareLocation);
	REQUIRE(map.value("temperatureUnit").value<Settings::TemperatureUnit>() == temperatureUnit);
  }

  SECTION("Test if function toVariant correctly saves locations")
  {
	// Arrange
	QList<GeoLocationData> savedLocations = Settings::instance().savedLocations();

	// Act
	auto map = Settings::instance().toVariant().toMap();

	QList<GeoLocationData> savedLocationsFromVariant;

	const auto locations = map.value("locations").toList();
	for (const auto &location : locations)
	{
	  const auto geoLocation = location.toMap();
	  savedLocationsFromVariant.append(GeoLocationData::fromVariantMap(geoLocation));
	}
	// Assert
	REQUIRE(savedLocations == savedLocationsFromVariant);
  }

  SECTION("Test if function fromVariant correctly sets Settings variable")
  {
	// Arrange
	QVariantMap map;
	bool		shareLocation = true;
	map.insert("shareLocation", shareLocation);
	map.insert("temperatureUnit", QVariant::fromValue(Settings::TemperatureUnit::CELSIUS));
	map.insert("windSpeedUnit", QVariant::fromValue(Settings::WindSpeedUnit::KMH));
	map.insert("precipitationUnit", QVariant::fromValue(Settings::PrecipitationUnit::MILLIMETRES));

	QList<QVariant>		   locationList;
	QList<GeoLocationData> geoLocationList;
	GeoLocationData		   location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	geoLocationList.append(location);
	locationList.append(QVariant::fromValue(location));
	map.insert("locations", QVariant::fromValue(locationList));

	// Act
	Settings::instance().fromVariant(map);

	// Assert
	REQUIRE(shareLocation == Settings::instance().shareLocation());
  }

  SECTION("Settings serialization and deserialization")
  {
	// Arrange
	bool shareLocation = Settings::instance().shareLocation();

	// Act
	QVariant map = Settings::instance().toVariant();
	Settings::instance().fromVariant(map);

	// Assert
	REQUIRE(shareLocation == Settings::instance().shareLocation());
  }
}
