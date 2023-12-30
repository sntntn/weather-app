#include "catch.hpp"

#include "HomePage.h"
#include "MainWindow.h"

TEST_CASE("Test HomePage initialization")
{
    SECTION("HomePage Constructor Test")
    {
        // Arrange
        MainWindow* mainwindow = new MainWindow();

        // Act
        HomePage* homePage = new HomePage(mainwindow);

        // Assert
        REQUIRE(homePage != nullptr);
    }
}


