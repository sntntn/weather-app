#include "catch.hpp"

#include "ErrorWidget.h"

TEST_CASE("Test ErrorWidget initialization")
{
    SECTION("ErrorWidget Constructor Test")
    {
        // Arrange

        // Act
        ErrorWidget* errorWidget = new ErrorWidget(nullptr);

        // Assert
        REQUIRE(errorWidget != nullptr);
    }
}
