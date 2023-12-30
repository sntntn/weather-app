#include "catch.hpp"

#include "HomePage.h"
#include "MainWindow.h"
#include "qstackedwidget.h"
#include "qtimezone.h"
#include "WeatherData.h"

TEST_CASE("HomePage Tests")
{
    SECTION("Initialization")
    {
        // Arrange
        MainWindow* mainwindow = new MainWindow();

        // Act
        HomePage* homePage = new HomePage(mainwindow);

        // Assert
        REQUIRE(homePage != nullptr);
    }


    SECTION("Test addNewWidget function") {
        // Arrange
        qRegisterMetaType<QSharedPointer<WeatherData>>("QSharedPointer<WeatherData>");

        MainWindow* mainwindow = new MainWindow();
        auto stackedWidget = new QStackedWidget();
        HomePage *page = new HomePage(mainwindow);
        stackedWidget->addWidget(page);
        stackedWidget->setCurrentWidget(page);
        int numofWidgets = page->numWidgets();

        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QTimeZone timezone("Europe/Belgrade");

        QSharedPointer<WeatherData> sharedWeatherData = QSharedPointer<WeatherData>::create(
            location, 25, 30, 20, 65, true, timezone);

        // Act
        page->addNewWidget(sharedWeatherData);

        // Assert
        REQUIRE(numofWidgets + 1 == page->numWidgets());
    }

    SECTION("Test deleteWidgets function"){
        // Arrange
        qRegisterMetaType<QSharedPointer<WeatherData>>("QSharedPointer<WeatherData>");

        MainWindow* mainwindow = new MainWindow();
        auto stackedWidget = new QStackedWidget();
        HomePage *page = new HomePage(mainwindow);
        stackedWidget->addWidget(page);
        stackedWidget->setCurrentWidget(page);

        GeoLocationData location("Belgrade", "Belgrade", QGeoCoordinate(44.8125, 20.4375), "Serbia");
        QTimeZone timezone("Europe/Belgrade");

        QSharedPointer<WeatherData> sharedWeatherData = QSharedPointer<WeatherData>::create(
            location, 25, 30, 20, 65, true, timezone);

        page->addNewWidget(sharedWeatherData);

        // Act
        page->deleteWidgets();

        // Assert
        REQUIRE(page->numWidgets() == 0);
    }
}



