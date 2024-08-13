#include "catch.hpp"

#include <QSharedPointer>
#include <QSignalSpy>
#include <QStackedWidget>
#include <QTest>

#include "DetailedWeatherAPI.h"
#include "DetailedWeatherPage.h"
#include "MainWindow.h"
#include "WeatherData.h"

TEST_CASE("DetailedWeatherPage Tests")
{

  SECTION("Initialization")
  {
	// Arrange
	MainWindow *mainwindow = new MainWindow();

	// Act
	DetailedWeatherPage *page = new DetailedWeatherPage(mainwindow);

	// Assert
	REQUIRE(page != nullptr);
  }

  SECTION("Test addNewWidget function")
  {
	// Arrange
	qRegisterMetaType<QSharedPointer<WeatherData>>("QSharedPointer<WeatherData>");

	MainWindow			*mainwindow	   = new MainWindow();
	auto				 stackedWidget = new QStackedWidget();
	DetailedWeatherPage *page		   = new DetailedWeatherPage(mainwindow);
	stackedWidget->addWidget(page);
	stackedWidget->setCurrentWidget(page);
	int numofWidgets = page->numWidgets();

	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	QTimeZone		timezone("Europe/Belgrade");

	QSharedPointer<WeatherData> sharedWeatherData =
		QSharedPointer<WeatherData>::create(location, 25, 30, 20, 65, true, timezone);

	// Act
	page->addNewWidget(sharedWeatherData);

	// Assert
	REQUIRE(numofWidgets + 1 == page->numWidgets());
  }

  SECTION("deleteWidgets function")
  {
	// Arrange
	qRegisterMetaType<QSharedPointer<WeatherData>>("QSharedPointer<WeatherData>");

	MainWindow			*mainwindow	   = new MainWindow();
	auto				 stackedWidget = new QStackedWidget();
	DetailedWeatherPage *page		   = new DetailedWeatherPage(mainwindow);
	stackedWidget->addWidget(page);
	stackedWidget->setCurrentWidget(page);

	GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
	QTimeZone		timezone("Europe/Belgrade");

	QSharedPointer<WeatherData> sharedWeatherData =
		QSharedPointer<WeatherData>::create(location, 25, 30, 20, 65, true, timezone);

	page->addNewWidget(sharedWeatherData);

	// Act
	page->deleteWidgets();

	// Assert
	REQUIRE(page->numWidgets() == 0);
  }

  SECTION("Test if getData function calls function setData")
  {
	// Arrange
	qRegisterMetaType<QSharedPointer<DetailedWeatherData>>("QSharedPointer<DetailedWeatherData>");
	MainWindow			*mainwindow	   = new MainWindow();
	auto				 stackedWidget = new QStackedWidget();
	DetailedWeatherPage *page		   = new DetailedWeatherPage(mainwindow);
	stackedWidget->addWidget(page);
	stackedWidget->setCurrentWidget(page);
	GeoLocationData location("Izmisljeni", "Grad", QGeoCoordinate(44.8125, 20.4375), "Serbia");

	// Act
	QSignalSpy spy(page->api, &DetailedWeatherAPI::dataFetched);
	page->getData(location);

	QTest::qWait(1500);

	// Assert
	REQUIRE(spy.count() == 1);
  }
}
