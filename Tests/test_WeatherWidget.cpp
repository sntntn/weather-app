#include "GeoLocationData.h"
#include "catch.hpp"

#include "WeatherData.h"
#include "WeatherWidget.h"
#include "qgeocoordinate.h"
#include "qtimezone.h"

TEST_CASE("Test WeatherWidget initialization")
{
  SECTION("WeatherWidget Constructor Test")
  {
	// Arrange
	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	QTimeZone		timezone("Europe/Belgrade");

	QSharedPointer<WeatherData> sharedWeatherData =
		QSharedPointer<WeatherData>::create(location, 25, 30, 20, 65, true, timezone);

	// Act
	WeatherWidget *weatherWidget = new WeatherWidget(sharedWeatherData, nullptr);

	// Assert
	REQUIRE(weatherWidget != nullptr);
  }
}
