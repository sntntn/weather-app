#include "DetailedWeatherData.h"
#include "GeoLocationData.h"
#include "catch.hpp"

TEST_CASE("DetailedWeatherData Construction")
{
  GeoLocationData  location("Belgrade", "Belgrade City", QGeoCoordinate(44.8125, 20.4375), "Serbia");
  QVector<int>	   hourlyTemperature{20, 25, 30, 35};
  QVector<int>	   fullHourlyTemperature{20, 25, 30, 35, 40, 45, 50};
  QVector<int>	   hourlyCode{100, 200, 300, 400};
  QVector<bool>	   hourlyIsDay{true, false, true, false};
  QVector<QString> hourlyTimeStamp{"12:00", "15:00", "18:00", "21:00"};
  QVector<int>	   weeklyMaxTemp{30, 35, 40};
  QVector<int>	   weeklyMinTemp{20, 25, 30};
  QVector<int>	   weeklyCode{500, 600, 700};
  QVector<QString> sunrise{"06:00", "06:30", "07:00"};
  QVector<QString> sunset{"18:00", "18:30", "19:00"};
  QVector<QString> weeklyDayName{"Monday", "Tuesday", "Wednesday"};

  DetailedWeatherData weatherData(location, 25, 200, true, QTimeZone("Europe/Belgrade"), 10, 15, 180, 30, 5, 0.5, 7, 60,
								  10, 1010, hourlyTemperature, fullHourlyTemperature, hourlyCode, hourlyIsDay,
								  hourlyTimeStamp, weeklyMaxTemp, weeklyMinTemp, weeklyCode, sunrise, sunset,
								  weeklyDayName);

  SECTION("Check GeoLocationData")
  {
	REQUIRE(weatherData.location() == location);
  }

  SECTION("Check Basic WeatherData Properties")
  {
	REQUIRE(weatherData.temperature() == 25);
	REQUIRE(weatherData.weatherCode() == 200);
	REQUIRE(weatherData.isDay() == true);
	REQUIRE(weatherData.timezone() == QTimeZone("Europe/Belgrade"));
  }

  SECTION("Check DetailedWeatherData Properties")
  {
	REQUIRE(weatherData.windSpeed() == 10);
	REQUIRE(weatherData.windGusts() == 15);
	REQUIRE(weatherData.windDirection() == 180);
	REQUIRE(weatherData.apparentTemperature() == 30);
	REQUIRE(weatherData.precipitation() == 5);
	REQUIRE(weatherData.snowDepth() == 0.5);
	REQUIRE(weatherData.uvIndex() == 7);
	REQUIRE(weatherData.humidity() == 60);
	REQUIRE(weatherData.visibility() == 10);
	REQUIRE(weatherData.pressure() == 1010);
  }

  SECTION("Check Hourly Temperature Data")
  {
	REQUIRE(weatherData.hourlyTemperature() == hourlyTemperature);
	REQUIRE(weatherData.fullHourlyTemperature() == fullHourlyTemperature);
	REQUIRE(weatherData.hourlyCode() == hourlyCode);
	REQUIRE(weatherData.hourlyIsDay() == hourlyIsDay);
	REQUIRE(weatherData.hourlyTimeStamp() == hourlyTimeStamp);
  }

  SECTION("Check Weekly Temperature Data")
  {
	REQUIRE(weatherData.weeklyMaxTemp() == weeklyMaxTemp);
	REQUIRE(weatherData.weeklyMinTemp() == weeklyMinTemp);
	REQUIRE(weatherData.weeklyCode() == weeklyCode);
	REQUIRE(weatherData.sunrise() == sunrise);
	REQUIRE(weatherData.sunset() == sunset);
	REQUIRE(weatherData.weeklyDayName() == weeklyDayName);
  }
}
