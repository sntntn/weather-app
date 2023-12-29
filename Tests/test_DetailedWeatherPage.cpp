#include "catch.hpp"

#include <QSignalSpy>
#include <QTest>
#include <QSharedPointer>

#include "MainWindow.h"
#include "WeatherData.h"
#include "DetailedWeatherPage.h"
#include "DetailedWeatherAPI.h"

TEST_CASE("DetailedWeatherPage Tests"){

    SECTION("Initialization") {
        // Arrange
        MainWindow* mainwindow = new MainWindow();
        DetailedWeatherPage *page = new DetailedWeatherPage(mainwindow);

        // Act

        // Assert
        REQUIRE(page != nullptr);
    }

    SECTION("Add New Weather Widget") {
        // Arrange
        qRegisterMetaType<QSharedPointer<WeatherData>>("QSharedPointer<WeatherData>");

        MainWindow* mainwindow = new MainWindow();
        DetailedWeatherPage page(mainwindow);
        int numofWidgets = page.widgetNumber();

        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QTimeZone timezone("Europe/Belgrade");

        QSharedPointer<WeatherData> sharedWeatherData = QSharedPointer<WeatherData>::create(
            location, 25, 30, 20, 65, true, timezone);

        // Act
        page.addNewWidget(sharedWeatherData);

        QTest::qWait(1000);

        // Assert
        REQUIRE(numofWidgets + 1 == page.widgetNumber());
    }


    SECTION("Test if getData function calls function setData") {
        //Arrange
        MainWindow* mainwindow = new MainWindow();
        DetailedWeatherPage page(mainwindow);
        GeoLocationData location("Izmisljeni", "Grad", QGeoCoordinate(44.8125, 20.4375), "Serbia");

        //Act
        QSignalSpy spy(page.api, &DetailedWeatherAPI::dataFetched);
        page.getData(location);

        QTest::qWait(1000);

        //Assert
        REQUIRE(spy.count() == 1);
    }
}

