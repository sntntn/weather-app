#include "catch.hpp"

#include "BasicWidget.h"

TEST_CASE("Test BasicWidget initialization")
{
  SECTION("BasicWidget Constructor Test")
  {
	// Arrange

	// Act
	BasicWidget *basicWidget = new BasicWidget(nullptr);

	// Assert
	REQUIRE(basicWidget != nullptr);
  }
}
