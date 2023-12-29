#include "catch.hpp"

#include <QObject>
#include <QTimer>
#include <QTest>

#include "UserLocation.h"

TEST_CASE("UserLocation signals"){
    SECTION("Either userLocationFetched or userLocationError"
            " is emitted when getLocation function is called"){
        // Arrange
        UserLocation userLocation;
        bool fetched = false;
        bool error = false;

        // Act
        QObject::connect(&userLocation, &UserLocation::userLocationFetched, [&fetched](){
            fetched = true;
        });

        QObject::connect(&userLocation, &UserLocation::userLocationError, [&error](){
            error = true;
        });

        userLocation.getLocation();
        QTest::qWait(1500);

        // Assert
        REQUIRE_FALSE(fetched == error);
    }
}

