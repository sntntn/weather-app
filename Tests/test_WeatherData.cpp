#include "catch.hpp"

#include "WeatherData.h"

TEST_CASE("Test WeatherData initialization")
{
  SECTION("WeatherData Constructor Test")
  {
	// Arrange
	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	int				temperature		   = 25;
	int				highestTemperature = 30;
	int				lowestTemperature  = 20;
	int				weatherCode		   = 65;
	bool			isDay			   = true;
	QTimeZone		timezone("Asia/Bangkok");

	// Act
	WeatherData weatherData(location, temperature, highestTemperature, lowestTemperature, weatherCode, isDay, timezone);

	// Assert
	REQUIRE(weatherData.temperature() == temperature);
	REQUIRE(weatherData.highestTemperature() == highestTemperature);
	REQUIRE(weatherData.lowestTemperature() == lowestTemperature);
	REQUIRE(weatherData.weatherCode() == weatherCode);
	REQUIRE(weatherData.isDay() == isDay);
	REQUIRE(weatherData.timezone() == timezone);
  }
}
