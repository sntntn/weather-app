#include "catch.hpp"

#include <QGeoCoordinate>
#include <QObject>
#include <QTest>
#include <QTimer>

#include "DetailedWeatherAPI.h"
#include "DetailedWeatherData.h"
#include "GeoLocationData.h"

TEST_CASE("DetailedWeatherAPI testing")
{
  SECTION("DetailedWeatherData sent with dataFetched signal contains "
		  "GeoLocationData which was sent to DetailedWeatherAPI")
  {
	// Arrange
	GeoLocationData	   location1("test", "test", QGeoCoordinate(4.99811, -73.85789), "test");
	GeoLocationData	   location2;
	DetailedWeatherAPI api;

	// Act
	QObject::connect(&api, &DetailedWeatherAPI::dataFetched,
					 [&location2](const QSharedPointer<DetailedWeatherData> &data)
					 { location2 = data.data()->location(); });

	api.fetchData(location1);
	QTest::qWait(1500);

	bool check = location1.getRenamedPlace() == location2.getRenamedPlace() &&
				 location1.getDetailedPlace() == location2.getDetailedPlace() &&
				 location1.getCountry() == location2.getCountry() &&
				 location1.getCoordinates() == location2.getCoordinates();

	// Assert
	REQUIRE(check);
  }

  SECTION("DetailedWeatherAPI returns errorOccurred signal if the coordinates are incorrect")
  {
	// Arrange
	GeoLocationData	   location1("test", "test", QGeoCoordinate(200.0, 200.0), "test");
	DetailedWeatherAPI api;
	bool			   errorOccurred = false;

	// Act
	QObject::connect(&api, &DetailedWeatherAPI::errorOccurred, [&errorOccurred]() { errorOccurred = true; });

	api.fetchData(location1);
	QTest::qWait(1500);

	// Assert
	REQUIRE(errorOccurred);
  }
}
