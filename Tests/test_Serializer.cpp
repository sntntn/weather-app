#include "catch.hpp"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QGeoCoordinate>
#include <QJsonDocument>
#include <QString>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "GeoLocationData.h"
#include "Serializer.h"

TEST_CASE("Serializer class")
{

  SECTION("Test if output file contains correct information")
  {
	// Arrange
	GeoLocationData location("Mombasa, Mvita, Kenya", "Mombasa", QGeoCoordinate(-4.05052, 39.667169), "Kenya");

	QString appPath = QCoreApplication::applicationDirPath();

	QString path1 = appPath + "/../Tests/Resources/serializer.json";
	QString path2 = appPath + "/../Tests/Resources/serializer_output.json";

	std::ifstream	  file1(path1.toUtf8().toStdString());
	std::stringstream buffer1;
	buffer1 << file1.rdbuf();
	std::string expectedJson = buffer1.str();

	// Act
	Serializer::save(location, path2);

	std::ifstream	  file2(path2.toUtf8().toStdString());
	std::stringstream buffer2;
	buffer2 << file2.rdbuf();
	std::string outputJson = buffer2.str();

	// Assert
	REQUIRE(expectedJson == outputJson);
  }

  SECTION("Test if serializer gets the correct information from a file")
  {
	// Arrange
	GeoLocationData expected("Mombasa, Mvita, Kenya", "Mombasa", QGeoCoordinate(-4.05052, 39.667169), "Kenya");

	QString path = QCoreApplication::applicationDirPath() + "/../Tests/Resources/serializer.json";

	// Act
	GeoLocationData location;
	Serializer::load(location, path);

	bool check = location.getCoordinates() == expected.getCoordinates() &&
				 location.getRenamedPlace() == expected.getRenamedPlace() &&
				 location.getDetailedPlace() == expected.getDetailedPlace();

	// Assert
	REQUIRE(check);
  }

  SECTION("Test if serializing and deserializing returns the same object")
  {
	// Arrange
	GeoLocationData expected("Mombasa, Mvita, Kenya", "Mombasa", QGeoCoordinate(-4.05052, 39.667169), "Kenya");
	QString			path = QCoreApplication::applicationDirPath() + "/../Tests/Resources/serializer_output.json";

	// Act
	Serializer::save(expected, path);
	GeoLocationData location;
	Serializer::load(location, path);

	bool check = location.getCoordinates() == expected.getCoordinates() &&
				 location.getRenamedPlace() == expected.getRenamedPlace() &&
				 location.getDetailedPlace() == expected.getDetailedPlace();

	// Assert
	REQUIRE(check);
  }
}
