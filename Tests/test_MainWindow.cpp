#include "catch.hpp"

#include <QObject>
#include <QTimer>

#include "MainWindow.h"
#include "HomePage.h"
#include "DetailedWeatherPage.h"
#include "GeoLocationData.h"

TEST_CASE("MainWindow page manipulation functions"){

    SECTION("Initial page is HomePage"){
        // Arrange
        MainWindow mainWindow;

        // Act
        auto currentPage = dynamic_cast<HomePage*>(mainWindow.currentPage());

        // Assert
        REQUIRE_FALSE(currentPage == nullptr);
    }

    SECTION("Current page is DetailedWeatherPage if showDetailedWeatherPage slot is triggered"){
        // Arrange
        MainWindow mainWindow;
        HomePage homePage;
        GeoLocationData geolocation;
        QObject::connect(&homePage, &HomePage::locationObjectSelected,
                         &mainWindow, &MainWindow::showDetailedWeatherPage);

        // Act
        emit homePage.locationObjectSelected(geolocation);
        auto currentPage = dynamic_cast<DetailedWeatherPage*>(mainWindow.currentPage());

        // Assert
        REQUIRE_FALSE(currentPage == nullptr);
    }

    SECTION("Current page is HomePage if showHomePage slot is triggered"){
        // Arrange
        MainWindow mainWindow;
        QTimer timer;
        QObject::connect(&timer, &QTimer::timeout,
                         &mainWindow, &MainWindow::showHomePage);

        // Act
        timer.start(1);
        auto currentPage = dynamic_cast<HomePage*>(mainWindow.currentPage());

        // Assert
        REQUIRE_FALSE(currentPage == nullptr);
    }
}

